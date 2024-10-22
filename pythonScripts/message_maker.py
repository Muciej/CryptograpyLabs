'''
Copyright by Arkadiusz Gaweł
'''

def message_maker(msg: str, name: str, bytes_format: int, inverse_bytes: bool = True):
    split_msg = [
        [word[0 + index: 2 + index] for index in range(0, 7, 2)][::(-1 if inverse_bytes else 1)] for word in msg.split()
    ]

    if bytes_format == 8:
        split_msg = [[f"0x{value}" for value in word] for word in split_msg]

    elif bytes_format == 16:
        split_msg = [[f"0x{value_1}{value_2}" for value_1, value_2 in zip(word[::2], word[1::2])] for word in split_msg]

    elif bytes_format == 32:
        split_msg = [["0x" + "".join(word)] for word in split_msg]

    else:
        print("Wrong format!")

    print(f"const uint{bytes_format}_t {name}[{int(64 * 8 / bytes_format)}] = "
          + "{\n\t" + ",\n\t".join([", ".join(word) for word in split_msg]) + "\n};")


if __name__ == '__main__':
    bytes_format = 32

    message_maker(
        "02dd31d1 c4eee6c5 069a3d69 5cf9af98 87b5ca2f ab7e4612 3e580440 897ffbb8 "
        "0634ad55 02b3f409 8388e483 5a417125 e8255108 9fc9cdf7 f2bd1dd9 5b3c3780",
        name="msg_0",
        bytes_format=bytes_format,
        inverse_bytes=False
    )
    message_maker(
        "d11d0b96 9c7b41dc f497d8e4 d555655a c79a7335 0cfdebf0 66f12930 8fb109d1 "
        "797f2775 eb5cd530 baade822 5c15cc79 ddcb74ed 6dd3c55f d80a9bb1 e3a7cc35",
        name="msg_1",
        bytes_format=bytes_format,
        inverse_bytes=False
    )
    message_maker(
        "02dd31d1 c4eee6c5 069a3d69 5cf9af98 07b5ca2f ab7e4612 3e580440 897ffbb8 "
        "0634ad55 02b3f409 8388e483 5a41f125 e8255108 9fc9cdf7 72bd1dd9 5b3c3780",
        name="msg_0_prime",
        bytes_format=bytes_format,
        inverse_bytes=False
    )
    message_maker(
        "d11d0b96 9c7b41dc f497d8e4 d555655a 479a7335 0cfdebf0 66f12930 8fb109d1 "
        "797f2775 eb5cd530 baade822 5c154c79 ddcb74ed 6dd3c55f 580a9bb1 e3a7cc35",
        name="msg_1_prime",
        bytes_format=bytes_format,
        inverse_bytes=False
    )
