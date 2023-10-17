import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Coder {
    private static final String str1 = "MVNO_ENC_TEST_01";
    private static byte[] pbUserKey = str1.getBytes();
    private static byte bszIV[] = {
            (byte) 0x026, (byte) 0x08d, (byte) 0x066, (byte) 0x0a7,
            (byte) 0x035, (byte) 0x0a8, (byte) 0x01a, (byte) 0x081,
            (byte) 0x06f, (byte) 0x0ba, (byte) 0x0d9, (byte) 0x0fa,
            (byte) 0x036, (byte) 0x016, (byte) 0x025, (byte) 0x001
    };

    public static void main(String[] args) throws IOException {
        if (args[0].equals("-t")) {
            testbed();
            return;
        }

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
                    if (f.getName().contains("Coder") || f.getName().contains("KISA_SEED_CBC") || f.getName().contains(".FIN"))
                        continue;
                    bytes = readFileToBytes(f.getPath());
                    if (args[0].equals("-e")) {
                        if (f.getName().contains(".enc"))
                            continue;
                        System.out.println("Encrypt File " + (++index) + ": " + f.getName() + "...");

                        if (bytes.length > 1024 * 1024 * 100) { // 1024 * 1024 * 100 byte ---> 1 MB
                            String path = f.getPath() + ".enc";

                            int prev = 0;
                            int pos = 1024 * 1024 * 100; // 1024 * 1024 * 100 byte ---> 1 MB
                            long len = bytes.length;
                            while (len >= 0) {
                                byte[] arr;
                                if (len < 1024 * 1024 * 100) { // 1024 * 1024 * 100 byte ---> 1 MB
                                    arr = new byte[(int) len];
                                    pos += len - 1024 * 1024 * 100; // 1024 * 1024 * 100 byte ---> 1 MB
                                }
                                else arr = new byte[1024 * 1024 * 100]; // 1024 * 1024 * 100 byte ---> 1 MB

                                for (int i = prev; i < pos; i++) {
                                    arr[i-prev] = bytes[i];
                                }
                                byte[] rst = KISA_SEED_CBC.SEED_CBC_Encrypt(pbUserKey, bszIV, arr, 0,
                                        arr.length);
                                overwriteBytesToFile(path, rst);

                                prev = pos;
                                pos += 1024 * 1024 * 100; // 1024 * 1024 * 100 byte ---> 1 MB
                                len -= 1024 * 1024 * 100; // 1024 * 1024 * 100 byte ---> 1 MB
                            }
                        } else {
                            result = KISA_SEED_CBC.SEED_CBC_Encrypt(pbUserKey, bszIV, bytes, 0,
                                    bytes.length);
                            String path = f.getPath() + ".enc";
                            writeBytesToFile(path, result);
                        }
                    } else if (args[0].equals("-d")) {
                        if (!f.getName().contains(".enc"))
                            continue;
                        System.out.println("Decrypt File " + (++index) + ": " + f.getName() + "...");

                        if (bytes.length > 1024 * 1024 * 100) { // 1024 * 1024 * 100 byte ---> 1 MB
                            String path = f.getPath().replace(".enc", ".dec");

                            int prev = 0;
                            int pos = 1024 * 1024 * 100 + 16; // 1024 * 1024 * 100 byte ---> 1 MB
                            long len = bytes.length;
                            while (len >= 0) {
                                byte[] arr;
                                if (len < 1024 * 1024 * 100 + 16) { // 1024 * 1024 * 100 byte ---> 1 MB
                                    arr = new byte[(int) len];
                                    pos += len - 1024 * 1024 * 100 - 16; // 1024 * 1024 * 100 byte ---> 1 MB
                                }
                                else arr = new byte[1024 * 1024 * 100 + 16]; // 1024 * 1024 * 100 byte ---> 1 MB

                                for (int i = prev; i < pos; i++) {
                                    arr[i-prev] = bytes[i];
                                }
                                byte[] rst = KISA_SEED_CBC.SEED_CBC_Decrypt(pbUserKey, bszIV, arr, 0, arr.length);
                                overwriteBytesToFile(path, rst);

                                prev = pos;
                                pos += 1024 * 1024 * 100 + 16; // 1024 * 1024 * 100 byte ---> 1 MB
                                len -= 1024 * 1024 * 100 + 16; // 1024 * 1024 * 100 byte ---> 1 MB

                            }
                        } else {
                            result = KISA_SEED_CBC.SEED_CBC_Decrypt(pbUserKey, bszIV, bytes, 0, bytes.length);
                            String path = f.getPath().replace(".enc", ".dec");
                            writeBytesToFile(path, result);
                        }

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

    private static void writeBytesToFile(String filePath, byte[] bytes)
            throws IOException {
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(filePath);
            if (bytes != null)
                fos.write(bytes);
        } finally {
            if (fos != null) {
                fos.close();
            }
        }
    }

    private static void overwriteBytesToFile(String filePath, byte[] bytes)
            throws IOException {
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(filePath, true);
            if (bytes != null)
                fos.write(bytes);
        } finally {
            if (fos != null) {
                fos.close();
            }
        }
    }

    private static void testbed() throws IOException {
        byte[] bytes1 = readFileToBytes("lowTest_ORIGIN.wsdl.enc");
        byte[] bytes2 = readFileToBytes("lowTest.wsdl.enc");

        for (int i = 0; i < bytes1.length; i++) {
            if ((bytes1[i] == bytes2[i]))
                System.out.println("idx: " + i + " -> " + bytes1[i] + " " + bytes2[i] + " : " + (bytes1[i] == bytes2[i]));
            else
                break;
        }
    }
}
