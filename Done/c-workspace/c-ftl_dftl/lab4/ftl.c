/*
 * Lab #4 : DFTL Simulator
 *  - Storage Architecture, SSE3069
 *
 * TA: Jinwoo Jeong, Hyunbin Kang
 * Prof: Dongkun Shin
 * Intelligent Embedded Software Laboratory
 * Sungkyunkwan University
 * http://nyx.skku.ac.kr
 */

#include "ftl.h"
#include <stdio.h>
#include <stdlib.h>


/* DFTL simulator
 * you must make CMT, GTD to use L2P cache
 * you must increase stats.cache_hit value when L2P is in CMT
 * when you can not find L2P in CMT, you must flush cache
 * and load target L2P in NAND through GTD and increase stats.cache_miss value
 */

#define N_BUFFERS (10)
#define BUFFER_SIZE (N_BUFFERS*SECTORS_PER_PAGE*SECTOR_SIZE)

#define FREE 0
#define DATA_HOT 1
#define DATA_COLD 2
#define TRANS_HOT 3
#define TRANS_COLD 4

#define TRUE 1
#define FALSE 0

static void map_write(u32, u32, u32);
static void map_read(u32, u32, u32);
static void map_garbage_collection(u32, int);
static void garbage_collection(u32, int);

void trans_defragmenter(u32, int, int);

u32 lpn_to_ppn(int);
void get_next(u32, u32 *, u32 *, int);

int find_cache_victim(u32);
void update_cache_count(u32, int);

void trans_defragmenter(u32, int, int);
void data_defragmenter(u32, int, int);


void ftl_write_direct(u32, u32, char, u32 *);
void ftl_flush();

int buffer_read(u32, u32, u32, u32 *, int *);

typedef struct {
    int gc_cnt;
    int map_gc_cnt;
    long host_write, host_read;
    long nand_write, nand_read;
    long gc_write, gc_read;
    long map_write, map_read;
    long map_gc_write, map_gc_read;
    long cache_hit;
    long cache_miss;
    
    long fragmenter_cnt;
    long fragmenter_write;
} FTL_STATS;

typedef struct {
    u32 PBN;
    u32 PPN;
} L2P;

typedef struct {
    u32 data[N_MAP_ENTRIES_PER_PAGE];
    int page;
    int dirty;
    int status;
} CMT;

typedef struct {
    u32 data[SECTORS_PER_PAGE];
    int lpn;
    int status;
} BUFFER;

extern FTL_STATS ftl_stats;

L2P *PMT;
L2P next_page[N_BANKS][5];
L2P gtd[N_BANKS][N_MAP_PAGES_PB];
CMT cmt[N_BANKS][N_CACHED_MAP_PAGE_PB];
BUFFER buffer[N_BUFFERS];

int caches[N_BANKS][N_CACHED_MAP_PAGE_PB];

int empty_page = N_BUFFERS;
int invalid_page[N_BANKS][BLKS_PER_BANK];

int data_block[N_BANKS];
int trans_block[N_BANKS];
int block_status[N_BANKS][BLKS_PER_BANK];

int sector_bitmap_buffer[N_BUFFERS][SECTORS_PER_PAGE];


static void map_write(u32 bank, u32 map_page, u32 cache_slot)
{
    /* you use this function when you must flush
     * cache from CMT to NAND MAP area
     * flush cache with LRU policy and fix GTD!!
     */
    if (!cmt[bank][cache_slot].dirty) {
        printf("ERROR : map_write call with clean cache_slot %d\n", cache_slot);
        return;
    }
    
    map_page = cmt[bank][cache_slot].page;
    int status = cmt[bank][cache_slot].status;
    
    u32 PBN = -1;
    u32 PPN = -1;
    
    get_next(bank, &PBN, &PPN, status+2);
    if (trans_block[bank] == N_PHY_MAP_BLK) {
        block_status[bank][PBN] = FREE;
        map_garbage_collection(bank, status+2);
        get_next(bank, &PBN, &PPN, status+2);
        trans_block[bank]--;
    }
    
    if (gtd[bank][map_page].PBN != -1)
        invalid_page[bank][gtd[bank][map_page].PBN]++;
    
    gtd[bank][map_page].PBN = PBN;
    gtd[bank][map_page].PPN = PPN;
    
    nand_write(bank, PBN, PPN, cmt[bank][cache_slot].data, &map_page);
    ftl_stats.map_write++;
    
    cmt[bank][cache_slot].page = -1;
    cmt[bank][cache_slot].dirty = 0;
    cmt[bank][cache_slot].status = 0;
    
    for (int i = 0; i < SECTORS_PER_PAGE; i++)
        cmt[bank][cache_slot].data[i] = 0xFFFFFFFF;
}

static void map_read(u32 bank, u32 map_page, u32 cache_slot) {
    /* you use this function when you must load
         * L2P from NAND MAP area to CMT
         * find L2P MAP with GTD and fill CMT!!
         */
    u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    if (cmt[bank][cache_slot].dirty)
        map_write(bank, cmt[bank][cache_slot].page, cache_slot);
    
    if (gtd[bank][map_page].PBN == -1) {
        cmt[bank][cache_slot].status = 0;
        
        for(int i = 0; i < SECTORS_PER_PAGE; i++)
            data[i] = 0xFFFFFFFF;
    } else {
        nand_read(bank, gtd[bank][map_page].PBN, gtd[bank][map_page].PPN, data, &spare_data);
        cmt[bank][cache_slot].status = block_status[bank][gtd[bank][map_page].PBN];
    }
    
    cmt[bank][cache_slot].page = map_page;
    cmt[bank][cache_slot].dirty = 0;
    
    for (int i = 0; i< SECTORS_PER_PAGE; i++)
        cmt[bank][cache_slot].data[i] = data[i];
    
    free(data);
}

static void map_garbage_collection(u32 bank, int type)
{
    ftl_stats.map_gc_cnt++;
    int invalid = 0;
    int victim = -1;
    int blk = -1;
    int page = 0;
    
    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (!block_status[bank][i]) {
            blk = i;
            break;
        }
    }
    
    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (block_status[bank][i] != type)
            continue;
        if (invalid_page[bank][i] > invalid) {
            invalid = invalid_page[bank][i];
            victim = i;
        }
    }
    
    if (victim == -1) {
        trans_defragmenter(bank, type, blk);
        next_page[bank][type].PBN = -1;
        next_page[bank][type].PPN = -1;
        
        return;
    }
    
    u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    for (int i = 0; i < PAGES_PER_BLK; i++) {
        nand_read(bank, victim, i, data, &spare_data);
        
        if (gtd[bank][spare_data].PBN != victim)
            continue;
        if (gtd[bank][spare_data].PPN != i)
            continue;
        
        nand_write(bank, blk, page, data, &spare_data);
        ftl_stats.map_gc_write++;
        gtd[bank][spare_data].PBN = blk;
        gtd[bank][spare_data].PPN = page++;
    }
    
    block_status[bank][blk] = type;
    block_status[bank][victim] = FREE;
    invalid_page[bank][victim] = 0;
    nand_erase(bank, victim);
    
    next_page[bank][type].PBN = blk;
    next_page[bank][type].PPN = page-1;
    
    free(data);
}

static void garbage_collection(u32 bank, int type)
{
    ftl_stats.gc_cnt++;
    int invalid = 0;
    int victim = -1;
    int blk = -1;
    int page = 0;
    
    u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (!block_status[bank][i]) {
            blk = i;
            break;
        }
    }
    
    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (block_status[bank][i] != type)
            continue;
        if (invalid_page[bank][i] > invalid) {
            invalid = invalid_page[bank][i];
            victim = i;
        }
    }
    
    if (victim == -1) {
        data_defragmenter(bank, type, blk);
        next_page[bank][type].PBN = -1;
        next_page[bank][type].PPN = -1;
        return;
    }
    
    block_status[bank][blk] = type;
    data_block[bank]++;
    
    for (int i = 0; i < PAGES_PER_BLK; i++) {
        nand_read(bank, victim, i, data, &spare_data);
        int index = (spare_data / N_BANKS) % SECTORS_PER_PAGE;
        u32 cache_slot = lpn_to_ppn(spare_data);
        
        if (cmt[bank][cache_slot].data[index] != victim * PAGES_PER_BLK + i)
            continue;
        nand_write(bank, blk, page, data, &spare_data);
        ftl_stats.gc_write++;
        
        index = (spare_data / N_BANKS) % SECTORS_PER_PAGE;
        cmt[bank][cache_slot].data[index] = blk * PAGES_PER_BLK + page++;
        cmt[bank][cache_slot].page = spare_data / (N_BANKS * SECTORS_PER_PAGE);
        cmt[bank][cache_slot].dirty = 1;
        cmt[bank][cache_slot].status = type;
        
    }
    
    block_status[bank][victim] = FREE;
    invalid_page[bank][victim] = 0;
    nand_erase(bank, victim);
    data_block[bank]--;
    
    next_page[bank][type].PBN = blk;
    next_page[bank][type].PPN = page-1;
    
    free(data);
}

void ftl_open()
{
    nand_init(N_BANKS, BLKS_PER_BANK, PAGES_PER_BLK);
    
    for (int i = 0; i < N_BANKS; i++) {
        next_page[i][1].PBN = -1;
        next_page[i][2].PBN = -1;
        next_page[i][3].PBN = -1;
        next_page[i][4].PBN = -1;
        
        next_page[i][1].PPN = -1;
        next_page[i][2].PPN = -1;
        next_page[i][3].PPN = -1;
        next_page[i][4].PPN = -1;
        
        for (int j = 0; j < N_CACHED_MAP_PAGE_PB; j++) {
            cmt[i][j].page = -1;
            cmt[i][j].dirty = 0;
            cmt[i][j].status = 0;
            
            for (int k = 0; k < N_MAP_ENTRIES_PER_PAGE; k++)
                cmt[i][j].data[k] = 0xFFFFFFFF;
        }
        
        for (int j = 0; j < N_MAP_PAGES_PB; j++) {
            gtd[i][j].PBN = -1;
            gtd[i][j].PPN = -1;
        }
    }
    
    for (int i = 0; i < N_BUFFERS; i++) {
        buffer[i].lpn = -1;
        buffer[i].status = 0;
    }
}



void ftl_read(u32 lba, u32 nsect, u32 *read_buffer)
{
    u32* data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32* buffer = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    
    int* bitmap = (int *)malloc(sizeof(int) * SECTORS_PER_PAGE);
    
    u32 spare_data;
    u32 lpn = lba / SECTORS_PER_PAGE;
    u32 index = lba % SECTORS_PER_PAGE;
    u32 tmpnsect = nsect;
    u32 rb_cursor = 0;
    
    while (TRUE) {
        for (int i = 0; i < SECTORS_PER_PAGE; i++)
            bitmap[i] = 0;
        
        if (buffer_read(lpn, index, tmpnsect, buffer, bitmap)) {
            for (int i = 0; i < SECTORS_PER_PAGE; i++)
                data[i] = buffer[i];
        } else {
            u32 bank = lpn % N_BANKS;
            u32 read = -1;
            u32 cache_slot = lpn_to_ppn(lpn);
            
            read = cmt[bank][cache_slot].data[(lpn / N_BANKS) % SECTORS_PER_PAGE];
            
            int pbn = read / PAGES_PER_BLK;
            int ppn = read % PAGES_PER_BLK;
            
            if (read == -1) {
                for (int i = 0; i < SECTORS_PER_PAGE; i++)
                    data[i] = 0xFFFFFFFF;
            } else
                nand_read(bank, pbn, ppn, data, &spare_data);
            
            for (int i = 0; i < SECTORS_PER_PAGE; i++)
                if (bitmap[i])
                    data[i] = buffer[i];
        }
        
        if (index + tmpnsect > SECTORS_PER_PAGE) {
            for (int i = index; i < SECTORS_PER_PAGE; i++)
                read_buffer[rb_cursor++] = data[i];
            
            tmpnsect -= SECTORS_PER_PAGE - index;
            index = 0;
            lpn++;
        } else {
            for (int i = index; i < index + tmpnsect; i++)
                read_buffer[rb_cursor++] = data[i];
            break;
        }
    }
    free(data);
    free(buffer);
    free(bitmap);
}


void ftl_write(u32 lba, u32 nsect, u32 *write_buffer)
{
    ftl_stats.host_write += nsect;
    u32 lpn = lba / SECTORS_PER_PAGE;
    u32 index = lba % SECTORS_PER_PAGE;
    
    u32 cursor = 0;
    u32 sector = nsect;
    
    while (TRUE) {
        if (!sector)
            break;
        
        int hit = 0;
        for (int i = 0; i < N_BUFFERS; i++) {
            if (buffer[i].lpn != lpn)
                continue;
            hit = 1;
            if (sector + index > SECTORS_PER_PAGE) {
                for (int j = index; j < SECTORS_PER_PAGE; j++) {
                    buffer[i].data[j] = write_buffer[cursor++];
                    sector_bitmap_buffer[i][j] = 1;
                }
                
                lpn++;
                sector = sector - SECTORS_PER_PAGE - index;
                index = 0;
                break;
            } else {
                for (int j = index; j < index+sector; j++) {
                    buffer[i].data[j] = write_buffer[cursor++];
                    sector_bitmap_buffer[i][j] = 1;
                }
                
                sector = 0;
                break;
            }
        }
        
        if (hit)
            continue;
        if (!empty_page)
            ftl_flush();
        
        for (int i = 0; i < N_BUFFERS; i++) {
            if (buffer[i].lpn != -1)
                continue;
            
            empty_page--;
            buffer[i].lpn = lpn;
            
            if (sector + index > SECTORS_PER_PAGE) {
                for (int j = index; j < SECTORS_PER_PAGE; j++) {
                    buffer[i].data[j] = write_buffer[cursor++];
                    sector_bitmap_buffer[i][j] = 1;
                }
                lpn++;
                sector = sector - SECTORS_PER_PAGE - index;
                index = 0;
            } else {
                for (int j = index; j < index + sector; j++) {
                    buffer[i].data[j] = write_buffer[cursor++];
                    sector_bitmap_buffer[i][j] = 1;
                }
                sector = 0;
            }
            break;
        }
    }
}


u32 lpn_to_ppn(int lpn)
{
    u32 cache_slot = -1;
    
    int cache_hit = 0;
    int bank = lpn % N_BANKS;
    int map_page = lpn / (N_BANKS * N_MAP_ENTRIES_PER_PAGE);
    
    for (int i = 0; i< N_CACHED_MAP_PAGE_PB; i++) {
        if (cmt[bank][i].page == map_page) {
            cache_hit = 1;
            ftl_stats.cache_hit++;
            update_cache_count(bank, i);
            return i;
        } else if (cmt[bank][i].page == -1)
            cache_slot = i;
    } if (!cache_hit) {
        ftl_stats.cache_miss++;
        if(cache_slot == -1) cache_slot = find_cache_victim(bank);
        map_read(bank, map_page, cache_slot);
        update_cache_count(bank, cache_slot);
        return cache_slot;
        
        
    }
    return -1;
}

void get_next(u32 bank, u32* nextPBN, u32* nextPPN, int status)
{
    if (next_page[bank][status].PPN + 1 >= PAGES_PER_BLK || next_page[bank][status].PBN == -1) {
        int flag = 0;
        
        for (int i = 0; i < BLKS_PER_BANK; i++) {
            if (!block_status[bank][i]) {
                next_page[bank][status].PBN = i;
                next_page[bank][status].PPN = 0;
                if (status == 1)
                    data_block[bank]++;
                else if (status == 2)
                    data_block[bank]++;
                else
                    trans_block[bank]++;
                block_status[bank][i] = status;
                flag = 1;
                
                break;
            }
        }
        if (!flag)
            printf("Error: NO FREE BLK!\n");
    }
    else
        next_page[bank][status].PPN++;
    
    *nextPBN = next_page[bank][status].PBN;
    *nextPPN = next_page[bank][status].PPN;
}

int find_cache_victim(u32 bank)
{
    int max = -1;
    int victim = -1;
    for (int i = 0; i < N_CACHED_MAP_PAGE_PB; i++)
        if (caches[bank][i] > max) {
            max = caches[bank][i];
            victim = i;
        }
    return victim;
}

void update_cache_count(u32 bank, int cache_slot)
{
    for (int i = 0; i < N_CACHED_MAP_PAGE_PB; i++) {
        if (i == cache_slot)
            caches[bank][i] = 0;
        else
            caches[bank][i]++;
    }
}

void trans_defragmenter(u32 bank, int type, int blk)
{
    ftl_stats.fragmenter_cnt++;
    
    u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    int page = 0;
    int next = -1;
    int workload;
    int erased = 0;
    
    if (type == 3)
        workload = 4;
    else
        workload = 3;

    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (i == blk)
            continue;
        if (block_status[bank][i] != workload)
            continue;
        if (invalid_page[bank][i] == 0)
            continue;
        
        for (int j = 0; j < PAGES_PER_BLK; j++) {
            nand_read(bank, i, j, data, &spare_data);
            if (gtd[bank][spare_data].PBN != i || gtd[bank][spare_data].PPN != j) {
                erased++;
                continue;
            } else {
                if (page == PAGES_PER_BLK) {
                    block_status[bank][blk] = workload;
                    blk = next;
                    page = 0;
                    trans_block[bank]++;
                }
                nand_write(bank, blk, page, data, &spare_data);
                ftl_stats.fragmenter_write++;
                gtd[bank][spare_data].PBN = blk;
                gtd[bank][spare_data].PPN = page++;
            }
        }
        
        nand_erase(bank, i);
        block_status[bank][i] = FREE;
        invalid_page[bank][i] = 0;
        trans_block[bank]--;
        next = i;
    }
    
    block_status[bank][blk] = workload;
    trans_block[bank]++;
    
    next_page[bank][workload].PBN = blk;
    next_page[bank][workload].PPN = page-1;
    
    if (erased < PAGES_PER_BLK)
        printf("Defragmenter Error : NAND is full!\n");
    free(data);
}


void data_defragmenter(u32 bank, int type, int blk)
{
    ftl_stats.fragmenter_cnt++;
    
    u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    int page = 0;
    int next = -1;
    int workload;
    int erased = 0;
    
    if (type == 1)
        workload = 2;
    else
        workload = 1;
    
    block_status[bank][blk] = workload;
    for (int i = 0; i < BLKS_PER_BANK; i++) {
        if (i == blk)
            continue;
        if (block_status[bank][i] != workload)
            continue;
        if (invalid_page[bank][i] == 0)
            continue;
        
        for (int j = 0; j < PAGES_PER_BLK; j++) {
            nand_read(bank, i, j, data, &spare_data);
            u32 cash_slot = lpn_to_ppn(spare_data);
            
            int index = (spare_data / N_BANKS) % SECTORS_PER_PAGE;
            if (cmt[bank][cash_slot].data[index] != i * PAGES_PER_BLK + j) {
                erased++;
                continue;
            } else {
                if (page == PAGES_PER_BLK) {
                    block_status[bank][next] = workload;
                    blk = next; page = 0;
                    data_block[bank]++;
                }
                
                nand_write(bank, blk, page, data, &spare_data);
                ftl_stats.fragmenter_write++;
                
                index = (spare_data / N_BANKS) % SECTORS_PER_PAGE;
                cmt[bank][cash_slot].data[index] = blk * PAGES_PER_BLK + page++;
                cmt[bank][cash_slot].page = spare_data / (N_BANKS * SECTORS_PER_PAGE);
                cmt[bank][cash_slot].dirty = 1;
                cmt[bank][cash_slot].status = type;
            }
        }
        
        nand_erase(bank, i);
        block_status[bank][i] = FREE;
        invalid_page[bank][i] = 0;
        data_block[bank]--;
        next = i;
    }
    data_block[bank]++;
    
    next_page[bank][workload].PBN = blk;
    next_page[bank][workload].PPN = page-1;
    
    if (erased < PAGES_PER_BLK)
        printf("Defragmenter Error : NAND is full!\n");
    
    free(data);
}

void ftl_write_direct(u32 lba, u32 nsect, char type, u32 *write_buffer)
{
    u32 lpn = lba / SECTORS_PER_PAGE;
    u32 index = lba % SECTORS_PER_PAGE;
    
    u32 *data  = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
    u32 spare_data;
    
    u32 sector = nsect;
    u32 wb_cursor = 0;
    
    int status;
    
    if (type =='H')
        status = DATA_HOT;
    else
        status = DATA_COLD;
    
    while (TRUE) {
        u32 bank = lpn % N_BANKS;
        for (int i = 0; i < SECTORS_PER_PAGE; i++)
            data[i] = 0xFFFFFFFF;
        
        u32 nextPBN = -1;
        u32 nextPPN = -1;
        
        get_next(bank, &nextPBN, &nextPPN, status);
        if (data_block[bank] == N_PHY_DATA_BLK) {
            block_status[bank][nextPBN] = FREE;
            data_block[bank]--;
            garbage_collection(bank, status);
            get_next(bank, &nextPBN, &nextPPN, status);
        }
        
        u32 page = lpn / (N_BANKS * SECTORS_PER_PAGE);
        u32 read = -1;
        u32 cache_slot = lpn_to_ppn(lpn);
        int index = (lpn / N_BANKS) % SECTORS_PER_PAGE;
        
        read = cmt[bank][cache_slot].data[index];
        
        cmt[bank][cache_slot].data[index] = nextPBN * PAGES_PER_BLK + nextPPN;
        cmt[bank][cache_slot].dirty = 1;
        cmt[bank][cache_slot].page = page;
        cmt[bank][cache_slot].status = status;
        
        if (read != -1) {
            int prePBN = read / PAGES_PER_BLK;
            int prePPN = read % PAGES_PER_BLK;
            
            invalid_page[bank][prePBN]++;
            nand_read(bank, prePBN, prePPN, data, &spare_data);
        }
        
        if (index + sector > SECTORS_PER_PAGE) {
            for (int i = 0; i < SECTORS_PER_PAGE; i++)
                if (i >= index && i < SECTORS_PER_PAGE)
                    data[i] = write_buffer[wb_cursor++];

            spare_data = lpn;
            nand_write(bank, nextPBN, nextPPN, data, &spare_data);
            ftl_stats.nand_write++;
            sector -= (SECTORS_PER_PAGE - index);
            index = 0;
            lpn++;
        } else {
            for (int i = 0; i < SECTORS_PER_PAGE; i++)
                if(i >= index && i < index + sector)
                    data[i] = write_buffer[wb_cursor++];

            spare_data = lpn;
            nand_write(bank, nextPBN, nextPPN, data, &spare_data);
            ftl_stats.nand_write++;
            break;
        }
        
    }
    
    free(data);
    return;
}


void ftl_flush()
{
    for (int i = 0; i < N_BUFFERS; i++) {
        int is_full = TRUE;
        for (int j = 0; j < SECTORS_PER_PAGE; j++) {
            if (sector_bitmap_buffer[i][j] == 0) {
                is_full = FALSE;
                break;
            }
        }
        
        if (is_full)
            ftl_write_direct(buffer[i].lpn * SECTORS_PER_PAGE, SECTORS_PER_PAGE, buffer[i].status, buffer[i].data);
        else {
            u32 *data = (u32 *)malloc(sizeof(u32) * SECTORS_PER_PAGE);
            u32 spare_data;
            
            u32 bank = buffer[i].lpn % N_BANKS;
            u32 index = (buffer[i].lpn / N_BANKS) % SECTORS_PER_PAGE;
            u32 cache_slot = lpn_to_ppn(buffer[i].lpn);
            u32 read = cmt[bank][cache_slot].data[index];
            
            if (read == -1) {
                for (int j = 0; j < SECTORS_PER_PAGE; j++)
                    data[j] = 0xFFFFFFFF;
            } else
                nand_read(bank, read / PAGES_PER_BLK, read % PAGES_PER_BLK, data, &spare_data);
            
            for (int j = 0; j < SECTORS_PER_PAGE; j++)
                if(sector_bitmap_buffer[i][j] == 1)
                    data[j] = buffer[i].data[j];
            
            ftl_write_direct(buffer[i].lpn * SECTORS_PER_PAGE, SECTORS_PER_PAGE, buffer[i].status, data);
        }
        
        buffer[i].lpn = -1;
        for(int j = 0; j < SECTORS_PER_PAGE; j++) {
            sector_bitmap_buffer[i][j] = 0;
        }
    }
    empty_page = N_BUFFERS;
}

int buffer_read(u32 lpn, u32 offset, u32 nsect, u32* read_buffer, int* sector_bitmap)
{
    int lpn_flag = 0;
    int bitmap_flag = 1;
    
    for (int i = 0; i < N_BUFFERS; i++) {
        if (buffer[i].lpn == lpn) {
            lpn_flag = 1;
            for (int j = offset; j < offset+nsect; j++) {
                if (j >= SECTORS_PER_PAGE)
                    break;
                if (sector_bitmap_buffer[i][j]) {
                    read_buffer[j] = buffer[i].data[j];
                    sector_bitmap[j] = 1;
                } else {
                    sector_bitmap[j] = 0;
                    bitmap_flag = 0;
                }
            }
            break;
        }
    }
    int result = lpn_flag * bitmap_flag;
    return result;
}
