from pymd5 import md5, padding
from urllib.parse import urlparse, parse_qs, quote, urlunparse

# 原始 URL
orig_url = ("https://cs.fdu.edu.cn/lab4/api?token=0f8349d0a9aa1da4d53749fdff404d28&user=stu&command1=ListFiles&command2=NoOp")

# 提取 token 和消息体
parts = urlparse(orig_url)
qs = parse_qs(parts.query, keep_blank_values=True)

token = qs['token'][0]
orig_query = "user=stu&command1=ListFiles&command2=NoOp"

# 长度扩展攻击参数
key_len = 8
pad = padding((key_len + len(orig_query)) * 8)
suffix = "&command3=DeleteAllFiles"

# 构造新 token（伪造哈希）
forge = md5(state=bytes.fromhex(token), count=(key_len + len(orig_query) + len(pad)) * 8)
forge.update(suffix.encode())
new_token = forge.hexdigest()

# 构造新 URL
pad_encoded = quote(pad.decode('latin-1'))
suffix_encoded = quote(suffix)
new_query = f"token={new_token}&{orig_query}{pad_encoded}{suffix_encoded}"
forge_url = urlunparse((parts.scheme, parts.netloc, parts.path, '', new_query, ''))

print("Forged URL:\n", forge_url)
