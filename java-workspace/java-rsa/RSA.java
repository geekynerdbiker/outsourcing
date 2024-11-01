import java.security.KeyPair;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.util.Base64;

public class RSA {
    public static void main(String[] args) throws Exception {
        KeyPair keyPair = Utility.genRSAKeyPair();

        PublicKey publicKey = keyPair.getPublic();
        PrivateKey privateKey = keyPair.getPrivate();

        String plainText = "김세윤 컴퓨터보안 프로젝트";

        String encrypted = Utility.encryptRSA(plainText, publicKey);
        System.out.println("Encrypted : " + encrypted);

        String decrypted = Utility.decryptRSA(encrypted, privateKey);
        System.out.println("Decrypted : " + decrypted);

        byte[] bytePublicKey = publicKey.getEncoded();
        String base64PublicKey = Base64.getEncoder().encodeToString(bytePublicKey);
        System.out.println("Base64 Public Key : " + base64PublicKey);

        byte[] bytePrivateKey = privateKey.getEncoded();
        String base64PrivateKey = Base64.getEncoder().encodeToString(bytePrivateKey);
        System.out.println("Base64 Private Key : " + base64PrivateKey);

        PrivateKey prKey = Utility.getPrivateKeyFromBase64String(base64PrivateKey);
        PublicKey puKey = Utility.getPublicKeyFromBase64String(base64PublicKey);

        String encrypted2 = Utility.encryptRSA(plainText, puKey);
        System.out.println("Encrypted : " + encrypted2);

        String decrypted2 = Utility.decryptRSA(encrypted, prKey);
        System.out.println("Decrypted : " + decrypted2);
    }
}