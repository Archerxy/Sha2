import static org.junit.Assert.*;

import java.nio.charset.Charset;
import java.security.MessageDigest;

import org.junit.Test;


public class Sha2Test {

    @Test
    public void test() {
        assertEquals(actual256("abc") + " != " + my256("abc"), actual256("abc"), my256("abc"));
        assertEquals(actual256("Hello") + " != " + my256("Hello"), actual256("Hello"), my256("Hello"));
        assertEquals(actual256("0") + " != " + my256("0"), actual256("0"), my256("0"));
        assertEquals(actual256("") + " != " + my256(""), actual256(""), my256(""));
        assertEquals(actual256("123456789") + " != " + my256("123456789"), actual256("123456789"), my256("123456789"));
        assertEquals(actual256("!@##$%%^&*()") + " != " + my256("!@##$%%^&*()"), actual256("!@##$%%^&*()"), my256("!@##$%%^&*()"));
        assertEquals(actual256("abcdefghijklmnop") + " != " + my256("abcdefghijklmnop"), actual256("abcdefghijklmnop"), my256("abcdefghijklmnop"));
        assertEquals(actual256(veryLargeString()) + " != " + my256(veryLargeString()), actual256(veryLargeString()), my256(veryLargeString()));
        assertEquals(actual256(multi256()) + " != " + my256(multi256()), actual256(multi256()), my256(multi256()));

        assertEquals(actual512("Hello") + " != " + my512("Hello"), actual512("Hello"), my512("Hello"));
        assertEquals(actual512("0") + " != " + my512("0"), actual512("0"), my512("0"));
        assertEquals(actual512("") + " != " + my512(""), actual512(""), my512(""));
        assertEquals(actual512("123456789") + " != " + my512("123456789"), actual512("123456789"), my512("123456789"));
        assertEquals(actual512("!@##$%%^&*()") + " != " + my512("!@##$%%^&*()"), actual512("!@##$%%^&*()"), my512("!@##$%%^&*()"));
        assertEquals(actual512("abcdefghijklmnop") + " != " + my512("abcdefghijklmnop"), actual512("abcdefghijklmnop"), my512("abcdefghijklmnop"));
        assertEquals(actual512(veryLargeString()) + " != " + my256(veryLargeString()), actual512(veryLargeString()), my512(veryLargeString()));
        assertEquals(actual512(multi512()) + " != " + my512(multi512()), actual512(multi512()), my512(multi512()));
    }
    
public String multi256() {
    return "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
}

public String multi512() {
    return "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhij"
            + "klmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
}
    
public String veryLargeString() {

    String output = "";
    for (int i = 0; i < 100000 ; i++) {
        output += "a";
    }
    return output;
}

public String my256(String value) {
    Charset cs = Charset.forName("UTF-8");
    byte[] data = value.getBytes(cs);
    byte[] hash = Sha256.encode(data);

    StringBuilder hex = new StringBuilder(hash.length * 2);
    int len = hash.length;
    for (int i = 0 ; i < len ; i++) {
        hex.append(String.format("%02X", hash[i]));
    }       
    return hex.toString();

}

public String my512(String value) {
    Charset cs = Charset.forName("UTF-8");
    byte[] data = value.getBytes(cs);
    byte[] hash = Sha512.encode(data);

    StringBuilder hex = new StringBuilder(hash.length * 2);
    int len = hash.length;
    for (int i = 0 ; i < len ; i++) {
        hex.append(String.format("%02X", hash[i]));
    }       
    return hex.toString();

}

public String actual256(String value) {
    try {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.reset();
        md.update(value.getBytes("UTF-8"));
        byte[] actual = md.digest();
        int actual_len = actual.length;
        StringBuilder actual_hex = new StringBuilder(actual.length * 2);
        for (int i = 0 ; i < actual_len ; i++) {
            actual_hex.append(String.format("%02X", actual[i]));
        }
        return actual_hex.toString();       
    } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
    }
    return null;
}

public String actual512(String value) {
    try {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.reset();
        md.update(value.getBytes("UTF-8"));
        byte[] actual = md.digest();
        int actual_len = actual.length;
        StringBuilder actual_hex = new StringBuilder(actual.length * 2);
        for (int i = 0 ; i < actual_len ; i++) {
            actual_hex.append(String.format("%02X", actual[i]));
        }
        return actual_hex.toString();       
    } catch (Exception e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
    }
    return null;
}
}
