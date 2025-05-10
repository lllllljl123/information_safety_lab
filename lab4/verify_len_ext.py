from pymd5 import md5, padding

# 计算原始信息的哈希
M = b"Use HMAC, not hashes"
orig_md5 = md5()
orig_md5.update(M)
h_M = orig_md5.hexdigest()

# 构造原始信息的填充
pad = padding(len(M) * 8)

# 伪造哈希值
suffix = b"Good advice"
forge_md5 = md5(state=bytes.fromhex(h_M), count=(len(M) + len(pad)) * 8)
forge_md5.update(suffix)
h_forge = forge_md5.hexdigest()

# 验证伪造信息的哈希是否匹配
fake_msg = M + pad + suffix
check_md5 = md5()
check_md5.update(fake_msg)
h_check = check_md5.hexdigest()

print("Original message hash :", h_M)
print("Extended message hash :", h_forge)
print("Hash of forged full message :", h_check)
