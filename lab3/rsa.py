import random
import math
import gmpy2

def multiplicative_inverse(e, phi):
    '''
    extended Euclid's algorithm for finding the multiplicative inverse 
    '''
    # WRITE YOUR CODE HERE!
    if e == 0:
        return (0, 1)  
    x1, y1 = multiplicative_inverse(phi % e, e)  
    x = y1 - (phi // e) * x1
    y = x1
    return (x, y)  


def key_generation(p, q):
    # WRITE YOUR CODE HERE!
    n = p * q
    phi = (p - 1) * (q - 1)
    e = random.randint(2,phi-1)
    d = multiplicative_inverse(e, phi)
    return ((e, n), (d, n))

def encrypt(pk, plaintext):
    # WRITE YOUR CODE HERE!
    e, n = pk
    m = int.from_bytes(plaintext.encode(), 'big')
    c = pow(m, e, n)
    return c

def decrypt(sk, ciphertext):
    # WRITE YOUR CODE HERE!
    d, n = sk
    m = pow(ciphertext, d, n)
    length = (m.bit_length() + 7) // 8
    return m.to_bytes(length, 'big').decode(errors='ignore')

def bytes2num(b): 
    s = '0x'
    for x in b:
        tmp = str(hex(x))[2:] 
        if len(tmp)==2:
            pass
        else:
            tmp = '0' +tmp 
        s += tmp
    num = int(s, 16) 
    return num

def num2str(n):
    tmp = str(hex(n))[2:] 
    if len(tmp)%2 == 0:
        pass 
    else:
        tmp = '0' +tmp 
    s = ''
    for i in range(0, len(tmp), 2): 
        temp = tmp[i] + tmp[i+1]
        s += chr(int(temp, 16))
    return s

if __name__ == "__main__":
    n = 87924348264132406875276140514499937145050893665602592992418171647042491658461
    p = 275127860351348928173285174381581152299
    q = 319576316814478949870590164193048041239
    e = 65537 
    phi_n = (p - 1) * (q - 1) 
    d = gmpy2.invert(e, phi_n)
    print(d)
    
    path = r'secret.enc'
    fi = open(path, 'rb') 
    cipher = fi.read()
    cipher = bytes2num(cipher)
    fi.close()

    de = decrypt((d, n), cipher)   
    print(de)

    st = "ManyQuestionMarks???"
    print(f"text: {st}")
    ci = encrypt((e, n), st)
    de = decrypt((d, n), ci)
    print(f"decode: {de}")
