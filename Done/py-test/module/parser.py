import struct
import os
import math

HEADER_SIGATURE = 'D0CF11E0A1B11AE1'

SIZE_OF_SECTOR          = 512
SIZE_OF_MINI_SECTOR     = 64
SIZE_OF_DIRECTORY_ENTRY = 4096

COMPOUND_HEADER_TOP_FORMAT      = '<8s16sHHHHHHIIIIIIIIII'
COMPOUND_HEADER_BOTTOM_FORMAT   = '<109I'
COMPOUND_FAT_SECTOR_FORMAT      = '<128I'
COMPOUND_DIRECTORY_ENTRY_FORMAT = '<64sHBBIII16sIQQIII'

EMPTY = 0xFFFFFFFF  # NON_DATA

TYPE_EMPTY        = 0
TYPE_STORAGE      = 1
TYPE_STREAM       = 2
TYPE_ROOT_STORAGE = 5

CP_ERROR          = False
CP_OK             = True


class DirectoryEntry:
    """ DirectoryEntry Class
            "Parser" Module

            .. note:: 파싱된 Directory Entry 정보 저장

            >>> "Example Code"
                DirectoryEntry()
    """
    def __init__(self):
        """
            .. notes:
                    [00H, 064] Directory Entry Name
                    [40H, 002] Directory Entry Name Length
                    [42H, 001] Object Type (root, storage, stream, unused)
                    [43H, 001] Color Flag
                    [44H, 004] Left Sibling ID
                    [48H, 004] Right Sibling ID
                    [4CH, 004] Child ID
                    [50H, 016] CLSID
                    [60H, 004] State Flags
                    [64H, 008] Creation Time
                    [6CH, 008] Modification Time
                    [74H, 004] Starting Sector Location
                    [48H, 004] Stream Size
                    [7CH, 002] reserved : must be zero
        """
        # print(" [CALLED] DirectoryEntry __init__ ")
        self.directory_entry_name = None
        self.directory_entry_name_length = None
        self.object_type = None
        self.color_flag = None
        self.stream_id_sibling_left = None
        self.stream_id_sibling_right = None
        self.stream_id_child = None
        self.clsid = None
        self.state_bits = None
        self.time_creation = None
        self.time_modified = None
        self.starting_sector_location = None
        self.stream_size = None
        self.padding = None
        self.chain_list = list()
        self.stream_data = b""

    def set_directory_entry(self, raw_directory_entry):
        """
            .. note:: entry의 데이터를 각 field 크기에 맞게 파싱하는 함수

            :param bytes raw_directory_entry: entry의 binary data (128bytes)

        """
        (
            self.directory_entry_name,
            self.directory_entry_name_length,
            self.object_type,
            self.color_flag,
            self.stream_id_sibling_left,
            self.stream_id_sibling_right,
            self.stream_id_child,
            self.clsid,
            self.state_bits,
            self.time_creation,
            self.time_modified,
            self.starting_sector_location,
            self.stream_size,
            self.padding
        ) = struct.unpack(COMPOUND_DIRECTORY_ENTRY_FORMAT, raw_directory_entry)

    def get_directory_entry_name(self):
        return self.directory_entry_name[:self.directory_entry_name_length - 2].decode("utf-16", "ignore")

    def get_object_type_explain(self):
        retStr = "exception"
        nType = self.object_type
        if nType == TYPE_EMPTY:
            retStr = "unused"
        if nType == TYPE_STORAGE:
            retStr = "storage"
        elif nType == TYPE_STREAM:
            retStr = "stream"
        elif nType == TYPE_ROOT_STORAGE:
            retStr = "root"
        return retStr


class CompoundHeader:
    """CompoundHeader Class

            .. note:: 파싱된 헤더의 값 파싱해 저장하는 함수 (파일의 첫 secter)

            >>> "Example Code"
                CompoundHeader()

    """
    def __init__(self):
        """
            ..note::
                    * header는 파일의 첫 섹터에 저장되어 있으며 크기는 512 Byte로,
                      파일에 대한 정보 header1(76 Byte) + __DIFAT 정보 header2(436 Byte)로 구성되어 있음\n

                    * header1\n
                    [00H, 008] HeaderSignature : must be [0xd0, 0xcf, 0x11, 0xe0, 0xa1, 0xb1, 0x1a, 0xe1]\n
                    [08H, 016] HeaderCLSID
                    [18H, 002] MinorVersion : minor version of the format\n
                    [1AH, 002] MajorVersion : major version of the dll/format\n
                    [1CH, 002] ByteOrder: indicates Intel byte-ordering (0xFEFF:Little, 0xFFFE:big)
                                          In a compound file, MUST be stored in Little Endian\n
                    [1EH, 002] SectorShift : size of sectors in power-of-two; 2^BlockSize
                                             if MajorVersion 3 == "0x09" then 2^0x9 = 512
                                             elif MajorVersion 4 == "0x0C" then 2^0xC(13) = 4096\n
                    [20H, 002] MiniSectorShift : size of mini-sectors in power-of-two; 2^sBlockSize
                                                 (default : "6", 2^6 = 64)\n
                    [22H, 002] reserved : must be zero\n
                    [24H, 004] reserved : must be zero\n
                    [28H, 004] NumberOfDirectorySectors : number of SECTs in directory chain for 4 KB sectors\n
                    [2CH, 004] NumberOfFATSectors : number of BLOCK in the BAT chain(bat index table __count) for BAT\n
                    [30H, 004] FirstDirectorySectorLocation : first Block in the directory chain (it is Root Directory sector)\n
                    [34H, 004] TransactionSignatureNumber : signature used for transactions, must be zero\n
                    [38H, 004] MiniStreamCutoffSize : [0x00001000] maximum size for a mini stream; typically 4096 bytes\n
                    [3CH, 004] FirstMiniFATSectorLocation : first SECT in the MiniFAT chain\n
                    [40H, 004] NumberOfMiniFATSectors : number of SECTs in the MiniFAT chain\n
                    [44H, 004] FirstDIFATSectorLocation : first SECT in the __DIFAT chain\n
                    [48H, 004] NumberOfDIFATSectors : number of SECTs in the __DIFAT chain; no __DIFAT less than 7MB\n

                    * header2\n
                    [4CH, 436] __DIFAT : FAT #n 's Location, first 109 FAT sector locations of compound file
    """
        # print(" [CALLED] CompoundHeader __init__ ")
        self.__header_signature = None
        self.__header_cls_id = None
        self.__minor_version = None
        self.__major_version = None
        self.__byte_order = None
        self.__sector_shift = None
        self.__mini_sector_shift = None
        self.__reserved1 = None
        self.__reserved2 = None
        self.__number_of_directory_sector = None
        self.__number_of_fat_sectors = None
        self.__first_directory_sector_location = None
        self.__transaction_signature = None
        self.__mini_stream_cutoff_size = None
        self.__first_mini_fat_sector_location = None
        self.__number_of_mini_fat_sectors = None
        self.__first_DIFAT_sector_location = None
        self.__number_of_DIFAT_sectors = None
        self.__DIFAT = None

    def set_header(self, buffer):
        """
                ..note:: header를 파싱하는 함수\n

                :param bytes buffer: header sector data

                :return:
                    success == 1(CP_OK)
                    failed == 0(CP_ERROR)
        """
        if not len(buffer) == SIZE_OF_SECTOR:
            return CP_ERROR

        baseline = struct.calcsize(COMPOUND_HEADER_TOP_FORMAT) # MUST be 76(0x4C) byte
        header1 = buffer[:baseline]
        header2 = buffer[baseline:]

        (
            self.__header_signature,
            self.__header_cls_id,
            self.__minor_version,
            self.__major_version,
            self.__byte_order,
            self.__sector_shift,
            self.__mini_sector_shift,
            self.__reserved1,
            self.__reserved2,
            self.__number_of_directory_sector,
            self.__number_of_fat_sectors,
            self.__first_directory_sector_location,
            self.__transaction_signature,
            self.__mini_stream_cutoff_size,
            self.__first_mini_fat_sector_location,
            self.__number_of_mini_fat_sectors,
            self.__first_DIFAT_sector_location,
            self.__number_of_DIFAT_sectors
        ) = struct.unpack(COMPOUND_HEADER_TOP_FORMAT, header1)

        self.__DIFAT = header2

        if self.__verify_header() == CP_ERROR:
            return CP_ERROR

        return CP_OK

    def __verify_header(self):
        if self.__header_signature != HEADER_SIGATURE:
            return CP_ERROR
        return CP_OK

    def get_number_of_fat_sector(self):
        return self.__number_of_fat_sectors

    def get_first_directory_sector_location(self):
        return self.__first_directory_sector_location

    def get_number_of_directory_sector(self):
        return self.__number_of_directory_sector

    def get_mini_stream_cutoff_size(self):
        return self.__mini_stream_cutoff_size

    def get_first_mini_fat_sector_location(self):
        return self.__first_mini_fat_sector_location

    def get_number_of_mini_fat_sectors(self):
        return self.__number_of_mini_fat_sectors

    def get_first_DIFAT_sector_location(self):
        return self.__first_DIFAT_sector_location

    def get_number_of_DIFAT_sectors(self):
        return self.__number_of_DIFAT_sectors

    def get_DIFAT(self):
        return self.__DIFAT


class CompoundFileReader:
    """CompoundFileReader_ Class
            "parser" Module의 메인 클래스

        .. note:: Compound 파일을 읽고 구조에 맞게 파싱하는 클래스

        >>> "Example Code"
            CompoundFileReader_("CBFB file name", 3)
            CompoundFileReader_(None, 2, 1, b"binarydata", False)
    """

    def __init__(self, filename, buffer=b"", is_path=True):
        """
            :param str filename: 파일 이름
            :param int count: 해당 파일의 depth 수준
            :param byte buffer: 전달해야 할 데이터가 존재할 경우(파일이 아닌 데이터 파싱할 때) 버퍼에 넣어서 전달
            :param bool is_path: 인풋이 파일이면 True, 인풋이 바이너리 데이터면 False

        """
        print(" [CALLED] CompoundFileReader_ __init__ ")
        self.__is_path = is_path
        if is_path:
            self.__filename = filename
            self.basefilename = os.path.basename(filename)
        else:
            self.__filename = None
            self.basefilename = None

        self.__fileBuf = buffer
        self.__fileSize = len(buffer)
        self.__Header = CompoundHeader()
        self.__numberOfSector = 0
        self.__DIFATArray = []
        self.__FATArray = []
        self.__miniFATArray = []  # 전체 miniFAT Entry를 list 형태로 저장
        self.__miniFATStream = b''      # Root Entry의 stream
        self.__directoryEntryArray = []
        self.__unallocatedData = []    # 미할당 영역을 담는 일종의 토큰이며, 리스트 임시 공간입니다.
        self.__usedFATSectorMap = []
        self.__usedMiniFATSectorMap = []

    def run(self):
        """CompoundFileReader_ 실행 메소드

                .. note::  CFBF 파일을 구조에 맞게 파싱 \n
                    openCompound() : 파일을 open하고 데이터를 read하는 함수 \n
                    setCompoundHeader() : Header 구조체에 맞게 매핑하는 함수 \n
                    setDIFATInfo() : DIFAT을 설정하는 함수 \n
                    setFATEntryStream() : FAT 구조에 맞게 설정 함수 \n
                    setMiniFATEntryStream() : MiniFAT 구조에 맞게 설정 함수 \n
                    setDirectoryEntryArray() : Header에서의 정보를 바탕으로 Directory Entry 저장 함수 \n
                    setMiniFATStream() : 구성된 MiniFAT를 이용하여 Stream 저장 함수 \n
                    readStreamToDirectoryEntry() : Directory Entry에서 해당 Entry에 해당하는 Stream 저자 함수 \n
                    setSlackmap() : 미사용, 미할당 영역을 취합해주는 함수

                :return:
                    parsing success  --  CP_OK
                    parsing fail or depth over --  CP_ERROR
        """
        if self.__open() == CP_ERROR:
            print("Open Compound Error")
            return CP_ERROR

        if self.__set_Header() == CP_ERROR:
            print("Set Compound Header Error")
            return CP_ERROR

        if self.__set_DIFATArray() == CP_ERROR:  # verify Big __filePointer (6.725MB ~)
            print("Set __DIFAT Error")
            return CP_ERROR

        if self.__set_FATEntry() == CP_ERROR:
            print("Set FAT Entry Stream Error")
            return CP_ERROR

        if self.__set_miniFATEntry() == CP_ERROR:
            print("Set MiniFAT Entry Stream Error")
            return CP_ERROR

        if self.__set_directoryEntryArray() == CP_ERROR:
            print("Set Directory Entry Array Error")
            return CP_ERROR

        if self.__set_miniFATStream() == CP_ERROR:
            print("Set MiniFAT Stream Error")
            return CP_ERROR

        if self.__read_stream_to_directoryEntry() == CP_ERROR:
            print("Read Stream Error")
            return CP_ERROR

        if self.__set_slack() == CP_ERROR:
            print("Set Slack Error")
            return CP_ERROR

        print("[-] Parser Success")
        return CP_OK

    def get_fileBuf(self):
        return self.__fileBuf

    def get_fileSize(self):
        return self.__fileSize

    def get_count(self):
        return self.__count

    def get_directoryEntryArray(self):
        return self.__directoryEntryArray

    def get_unallocatedData(self):
        return b"".join(self.__unallocatedData)

    def append_unallocatedData(self, tmp):
        self.__unallocatedData.append(tmp)

    def __open(self):
        if self.__is_path:
            with open(self.__filename, "rb") as filePointer:
                self.__fileBuf = filePointer.read()
                self.__fileSize = filePointer.tell()

        if self.__fileBuf == b"":
            print("[!] __filePointer Read Error!")
            return CP_ERROR
        if self.__fileSize < 512:
            print("[!] __filePointer Size < 512!")
            return CP_ERROR

        self.__fileBuf = [self.__fileBuf[i:i + SIZE_OF_SECTOR] for i in range(0, self.__fileSize, SIZE_OF_SECTOR)]
        self.__numberOfSector = len(self.__fileBuf)
        return CP_OK

    def __set_DIFATArray(self):
        raw_DIFAT = self.__Header.get_DIFAT()
        arr_DIFAT = struct.unpack(COMPOUND_HEADER_BOTTOM_FORMAT, raw_DIFAT)
        for index in range(len(arr_DIFAT)):
            if arr_DIFAT[index] == EMPTY:
                self.__DIFATArray = arr_DIFAT[:index]
                self.__unallocatedData.append(raw_DIFAT[index * 4:])
                return CP_OK

        num_of_DIFAT_sectors = self.__Header.get_number_of_DIFAT_sectors()
        if num_of_DIFAT_sectors > 0:
            next_sector = self.__Header.get_first_DIFAT_sector_location()
            for _ in range(num_of_DIFAT_sectors):
                raw_stream = self.__read_sector(next_sector)
                arr_tmp = struct.unpack(COMPOUND_FAT_SECTOR_FORMAT, raw_stream)
                for index in range(len(arr_tmp) - 1):
                    if arr_tmp[index] == EMPTY:
                        arr_DIFAT += arr_tmp[:index]
                        self.__unallocatedData.append(raw_stream[index * 4:])
                        self.__DIFATArray = arr_DIFAT
                        return CP_OK
                arr_DIFAT += arr_tmp
                next_sector = arr_tmp[-1]
            self.__DIFATArray = arr_DIFAT

    def __set_Header(self):
        sec_no = -1  # 헤더 섹터의 인덱스
        raw_stream = self.__read_sector(sec_no)
        
        # 해당 rawStream 값으로 헤더 구조체에 맞게 매핑
        # 자세한 구조체 내용은 set_header() 구조체를 확인
        if self.__Header.set_header(raw_stream) == CP_ERROR:
            return CP_ERROR
        return CP_OK

    def __set_miniFATEntry(self):
        sec_no = self.__Header.get_first_mini_fat_sector_location()
        loop = self.__Header.get_number_of_mini_fat_sectors()
        buf = b""
        if loop > 0:
            root_chain = self.__read_chain(sec_no, loop, self.__FATArray)
            if root_chain == CP_ERROR:
                return CP_ERROR
            buf = b"".join([self.__read_sector(root_chain[index]) for index in range(loop)])

        buf_len = len(buf)
        if buf_len % SIZE_OF_SECTOR:
            return CP_ERROR
        else:
            self.__miniFATArray = struct.unpack("<%dI" % (buf_len // 4), buf)
            return CP_OK

    def __set_FATEntry(self):
        buf = b"".join([self.__read_sector(index) for index in self.__DIFATArray])
        buf_len = len(buf)
        if buf_len % SIZE_OF_SECTOR:
            return CP_ERROR
        else:
            self.__FATArray = struct.unpack("<%dI" % (buf_len // 4), buf)[:self.__numberOfSector]

            return CP_OK

    def __set_directoryEntryArray(self):
        start_sector = self.__Header.get_first_directory_sector_location()
        entry_chain = self.__read_chain(start_sector, -1, self.__FATArray) # Directory Entry의 chain_size는 알 수 없음
        if entry_chain == CP_ERROR:
            return CP_ERROR
       
        buf = b"".join([self.__read_sector(sector) for sector in entry_chain])
        buf_len = len(buf)
        if buf_len % SIZE_OF_SECTOR or buf_len % SIZE_OF_DIRECTORY_ENTRY:  # len(buf)%512 != 0 -> readError, Exception
            print("[!] Error in __set_directoryEntryArray()")
            return CP_ERROR

        raw_stream = [buf[i:i + SIZE_OF_DIRECTORY_ENTRY] for i in range(0, buf_len, SIZE_OF_DIRECTORY_ENTRY)]
        for index in range(buf_len // SIZE_OF_DIRECTORY_ENTRY):
            temp_entry.set_directory_entry(raw_stream[index])
            self.__directoryEntryArray.append(temp_entry)
            if temp_entry.get_object_type_explain() == "unused" or temp_entry.get_object_type_explain() == "exception":
                self.__unallocatedData.append(raw_stream[index])
        return CP_OK

    def __set_miniFATStream(self):
        root_entry = self.__directoryEntryArray[0]
        if self.__Header.get_number_of_mini_fat_sectors() == 0 or self.__directoryEntryArray[0].stream_size == 0: # miniFAT stream이 없는 경우
            return CP_OK
        chain_size = math.ceil(self.__directoryEntryArray[0].stream_size / SIZE_OF_MINI_SECTOR)
        root_chain = self.__read_chain(root_entry.starting_sector_location, chain_size, self.__FATArray)
        if root_chain == CP_ERROR:
            return CP_ERROR

        rem = root_entry.stream_size % SIZE_OF_SECTOR
        buf = b"".join([self.__read_sector(index) for index in root_chain])
        if rem > 0:
            _ = SIZE_OF_SECTOR - rem
            buf = buf[:-_]
            self.append_unallocatedData(buf[-_:])

        buf_len = len(buf)
        if buf_len == 0:
            return CP_ERROR

        self.__miniFATStream = [buf[i:i + SIZE_OF_MINI_SECTOR] for i in range(0, buf_len, SIZE_OF_MINI_SECTOR)]
        return CP_OK

    def __read_stream_to_directoryEntry(self):
        for index in self.__directoryEntryArray:
            buf, size, start_sector = b"", index.stream_size, index.starting_sector_location
            if index.object_type == TYPE_STREAM and index.stream_size != 0:
                # mini-FAT
                if size < self.__Header.get_mini_stream_cutoff_size():
                    target_chain = self.__read_chain(start_sector, math.ceil(size / SIZE_OF_MINI_SECTOR), self.__miniFATArray)
                    if target_chain == CP_ERROR:
                        return CP_ERROR
                    buf = self.__read_stream_from_miniFATArray(size, target_chain)
                # FAT
                else:
                    target_chain = self.__read_chain(start_sector, math.ceil(size / SIZE_OF_SECTOR), self.__FATArray)
                    if target_chain == CP_ERROR:
                        return CP_ERROR
                    buf = self.__read_stream_from_FATArray(size, target_chain)

            if buf == CP_ERROR:
                return CP_ERROR
            index.stream_data = buf

        return CP_OK

    def __set_slack(self):
        end = self.__fileSize // SIZE_OF_SECTOR
        if self.get_fileSize() % SIZE_OF_SECTOR:
            end = end + 1
        FAT_slack_sector = list(set(range(end)) - set(self.__usedFATSectorMap))
        FATEntry_slack = list(set(range(len(self.__FATArray))) - set(self.__usedFATSectorMap))

        end = len(self.__miniFATStream)
        miniFAT_slack_sector = list(set(range(end)) - set(self.__usedMiniFATSectorMap))
        miniFATEntry_slack = list(set(range(len(self.__miniFATArray))) - set(self.__usedMiniFATSectorMap))

        # 미할당영역
        slack1 = [self.__miniFATStream[i] for i in miniFAT_slack_sector]
        slack2 = [self.__fileBuf[i] for i in FAT_slack_sector]
        slack3 = [int.to_bytes(self.__miniFATArray[i], 4, byteorder="little") for i in miniFATEntry_slack]
        slack4 = [int.to_bytes(self.__FATArray[i], 4, byteorder="little") for i in FATEntry_slack]
        self.__unallocatedData.append(b"".join(slack1 + slack2 + slack3 + slack4))
        return CP_OK

    def __read_sector(self, sector_number):
        sector_number = sector_number + 1
        if sector_number >= self.__numberOfSector:
            return b""
        self.__usedFATSectorMap.append(sector_number)
        return self.__fileBuf[sector_number]

    def __read_chain(self, first_chain, chain_size, array):
        if first_chain >= len(array):
            return CP_ERROR

        # END_OF_CHAIN 등을 만날 때 까지 체인을 구성
        if chain_size < 0: # Directory Entry의 chain
            target_chains = [first_chain]
            chain = first_chain
            while True:
                next_chain = array[chain]
                #2번 - 체인구성









            return target_chains
        else:
            target_chains = [first_chain]
            chain = first_chain
            for _ in range(chain_size + 1):
                next_chain = array[chain]
                #2번











            return target_chains

    def __read_stream_from_miniFATArray(self, stream_size, chain):
        buf_arr = []
        rem = stream_size % SIZE_OF_MINI_SECTOR
        try:
            for index in chain:
                buf_arr.append(self.__miniFATStream[index])
                self.__usedMiniFATSectorMap.append(index)
            if rem > 0:
                buf_arr[-1] = buf_arr[-1][:rem]
                self.__unallocatedData.append(buf_arr[-1][rem:])
        except IndexError:
            pass
        return b"".join(buf_arr)

    def __read_stream_from_FATArray(self, stream_size, chain):
        buf_arr = []
        rem = stream_size % SIZE_OF_SECTOR
        try:
            for index in chain:
                buf_arr.append(self.__read_sector(index))
            if rem > 0:
                buf_arr[-1] = buf_arr[-1][:rem]
                self.__unallocatedData.append(buf_arr[-1][rem:])
        except IndexError:
            pass
        return b"".join(buf_arr)
