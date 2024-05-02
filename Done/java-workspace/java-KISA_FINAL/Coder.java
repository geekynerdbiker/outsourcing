import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Coder {
    private static final int processBlockLen = 32;
    private static final int readBlockSize = 8192;

    private static final String str1 = "MVNO_ENC_TEST_01";
    private static KISA_SEED_CBC.KISA_SEED_INFO info = new KISA_SEED_CBC.KISA_SEED_INFO();
    private static byte[] pbUserKey = str1.getBytes();
    private static byte[] bszIV = {
            (byte) 0x026, (byte) 0x08d, (byte) 0x066, (byte) 0x0a7,
            (byte) 0x035, (byte) 0x0a8, (byte) 0x01a, (byte) 0x081,
            (byte) 0x06f, (byte) 0x0ba, (byte) 0x0d9, (byte) 0x0fa,
            (byte) 0x036, (byte) 0x016, (byte) 0x025, (byte) 0x001
    };
    private static byte[] inpbuf = new byte[80];
    private static int[] outbuf = new int[processBlockLen];
    private static int[] returnLen = {0};

    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("-e for Encrypt, -d for Decrypt");
        } else {
            byte[] bytes = null, result = null;
            File dir = new File(System.getProperty("user.dir"));
            File[] fileList = dir.listFiles();

            if (args.length >= 2) {
                for (int i = 0; i < fileList.length; i++)
                    for (int j = 1; j < args.length; j++) {
                        if (fileList[i].getName().contains(args[j]))
                            fileList[i] = null;
                    }
            }
            int index = 0;
            for (File f : fileList) {
                if (f == null)
                    continue;
                if (f.isFile()) {
                    if (f.getName().contains("Coder") || f.getName().contains("KISA_SEED_CBC") || f.getName().contains(".FIN") || f.getName().contains(".iml") || f.getName().contains(".DS"))
                        continue;

                    if (args[0].equals("-e")) {
                        if (f.getName().contains(".enc") || f.getName().contains(".dec"))
                            continue;
                        System.out.println("Encrypt File " + (++index) + ": " + f.getName() + "...");
                        Encrypt(f.getName());
                    } else if (args[0].equals("-d")) {
                        if (!f.getName().contains(".enc"))
                            continue;
                        System.out.println("Decrypt File " + (++index) + ": " + f.getName() + "...");
                        bytes = new byte[(int) f.length()];
                        Decrypt(f.getName());
                    } else {
                        System.out.println("Argument Error.");
                    }
                }
            }
            if (args[0].equals("-e")) {
                System.out.println("Encryption Done !");
            } else if (args[0].equals("-d")) {
                System.out.println("Decryption Done !");
            }
        }

    }

    private static byte[] readFileToBytes(String filePath) throws IOException {
        File file = new File(filePath);
        byte[] bytes = new byte[(int) file.length()];

        FileInputStream fis = null;
        try {
            fis = new FileInputStream(file);
            fis.read(bytes);

        } finally {
            if (fis != null) {
                fis.close();
            }
        }
        return bytes;
    }

    public static int Loop(byte[] dest, byte[] src, int size) {
        int i;
        int[] data;
        byte[] cdata;
        int remain = 0;

        for (i = 0; i < size - processBlockLen; ) {
            for (int j = 0; j < processBlockLen; j++)
                inpbuf[j] = src[j + i];
            data = KISA_SEED_CBC.chartoint32_for_SEED_CBC(inpbuf, processBlockLen);
            KISA_SEED_CBC.SEED_CBC_Process(info, data, processBlockLen, outbuf, returnLen);
            cdata = KISA_SEED_CBC.int32tochar_for_SEED_CBC(outbuf, returnLen[0]);
            for (int j = 0; j < returnLen[0]; j++)
                dest[j + i] = cdata[j];
            i += returnLen[0];
        }
        remain = size % processBlockLen;
        if (remain == 0)
            remain = processBlockLen;
        for (int j = 0; j < remain; j++)
            inpbuf[j] = src[j + i];
        data = KISA_SEED_CBC.chartoint32_for_SEED_CBC(inpbuf, remain);
        KISA_SEED_CBC.SEED_CBC_Process(info, data, remain, outbuf, returnLen);
        cdata = KISA_SEED_CBC.int32tochar_for_SEED_CBC(outbuf, returnLen[0]);
        for (int j = 0; j < returnLen[0]; j++)
            dest[j + i] = cdata[j];
        i += returnLen[0];

        return i;
    }

    public static void Encrypt(String path) {
        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(path);
            fos = new FileOutputStream(path + ".enc");

            byte[] temp = new byte[readBlockSize + 16];
            byte[] input = new byte[readBlockSize + 16];
            byte[] output = new byte[readBlockSize + 16];
            int size;
            int outputLen;
            byte[] cdata;
            int[] paddingLen = {0};
            int i;

            KISA_SEED_CBC.SEED_CBC_init(info, KISA_SEED_CBC.KISA_ENC_DEC.KISA_ENCRYPT, pbUserKey, bszIV);
            while (true) {
                size = fis.read(input);
                if (size <= 0)
                    break;
                if (size < readBlockSize)
                    break;
                outputLen = Loop(output, input, size);
                fos.write(output, 0, outputLen);
            }
            outputLen = Loop(output, input, size);

            KISA_SEED_CBC.SEED_CBC_Close(info, outbuf, 0, paddingLen);
            cdata = KISA_SEED_CBC.int32tochar_for_SEED_CBC(outbuf, paddingLen[0]);
            for (int j = 0; j < paddingLen[0]; j++)
                output[outputLen + j] = cdata[j];
            fos.write(output, 0, outputLen + paddingLen[0]);

            fis.close();
            fos.close();
        } finally {
            return;
        }
    }


    public static void Decrypt(String path) {
        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(path);
            fos = new FileOutputStream(path.replace(".enc", ".dec"));

            byte[] temp = new byte[readBlockSize + 16];
            byte[] input = new byte[readBlockSize + 16];
            byte[] output = new byte[readBlockSize + 16];
            int size;
            int outputLen;
            byte[] cdata;
            int[] paddingLen = {0};
            int i;

            KISA_SEED_CBC.SEED_CBC_init(info, KISA_SEED_CBC.KISA_ENC_DEC.KISA_DECRYPT, pbUserKey, bszIV);
            while (true) {
                size = fis.read(input);
                if (size <= 0)
                    break;
                if (size < readBlockSize)
                    break;
                outputLen = Loop(output, input, size);
                fos.write(output, 0, outputLen);
            }
            outputLen = Loop(output, input, size);

            int[] outbuf2 = new int[processBlockLen + outputLen / 4];
            for (int j = 0; j < outbuf.length; j++)
                outbuf2[j] = outbuf[j];
            int result = KISA_SEED_CBC.SEED_CBC_Close(info, outbuf2, outputLen / 4, paddingLen);
            if (result > 0)
                fos.write(output, 0, outputLen - paddingLen[0]);

            fis.close();
            fos.close();
        } finally {
            return;
        }

    }
}
