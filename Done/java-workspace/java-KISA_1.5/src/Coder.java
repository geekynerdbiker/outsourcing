import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Coder {
    private static byte[] pbUserKey = {(byte) 0x88, (byte) 0xE3, (byte) 0x4F, (byte) 0x8F, (byte) 0x08, (byte) 0x17, (byte) 0x79, (byte) 0xF1, (byte) 0xE9, (byte) 0xF3, (byte) 0x94, (byte) 0x37, (byte) 0x0A, (byte) 0xD4, (byte) 0x05, (byte) 0x89};
    private static byte bszIV[] = {
            (byte) 0x026, (byte) 0x08d, (byte) 0x066, (byte) 0x0a7,
            (byte) 0x035, (byte) 0x0a8, (byte) 0x01a, (byte) 0x081,
            (byte) 0x06f, (byte) 0x0ba, (byte) 0x0d9, (byte) 0x0fa,
            (byte) 0x036, (byte) 0x016, (byte) 0x025, (byte) 0x001
    };

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("-e for Encrypt, -d for Decrypt");
        } else if (args.length == 1) {
            byte[] bytes = null, result = null;
            File dir = new File(System.getProperty("user.dir"));
            File[] fileList = dir.listFiles();

            int index = 0;
            assert fileList != null;
            for (File f : fileList) {
                if (f.isFile()) {
                    if (f.getName().equals("Coder.java") || f.getName().toString().contains("KISA_SEED_CBC.java"))
                        continue;
                    try {
                        bytes = readFileToBytes(f.toPath().toString());
                        if (args[0].equals("-e")) {
                            System.out.println("Encrypt File" + (++index) + "...");

                            result = KISA_SEED_CBC.SEED_CBC_Encrypt(pbUserKey, bszIV, bytes, 0,
                                    bytes.length);
                            String path = f.getPath().toString();
                            writeBytesToFile(path, result);
                        } else if (args[0].equals("-d")) {
                            try {
                                System.out.println("Decrypt File" + (++index) + "...");
                                result = KISA_SEED_CBC.SEED_CBC_Decrypt(pbUserKey, bszIV, bytes, 0, bytes.length);
                                String path = f.getPath().toString();
                                writeBytesToFile(path, result);
                            } catch (NullPointerException e) {
                                e.getStackTrace();
                            }
                        } else {
                            System.out.println("Argument Error.");
                        }
                    } catch (IOException e) {
                        System.out.println("File Read Error.");
                    }
                }
            }
            if (args[0].equals("-e")) {
                System.out.println("Encryption Done !");
            } else if (args[0].equals("-d")) {
                System.out.println("Decryption Done !");
            }
        } else {
            System.out.println("Argument Error.");
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
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(bytes);
        }
    }
}
