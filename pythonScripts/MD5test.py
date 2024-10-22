from hashlib import md5

msgs = [b'TestMsg', b'HondaSzybszaNizWyglada', b'298502hsdfkjglkvbo2i3q4fuqofhslvkbiq2u3yf0q98273fqi23bflkjdbvlzkjdw3']

for msg in msgs:
    print(msg)
    print(md5(msg).digest().hex())
    print()

