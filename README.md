# ImCurr
File encryptor with open source code.

## Features
- Encrypt and decrypt files using **Blowfish** algorithm
- Compress folders into encrypted file containers
- Inject one file into another and eject back

#### [Download](https://github.com/shoraii/ImCurr/releases/tag/0.7.1) (Win32)
Both `ImCurr.exe` and `icengine.exe` have to be downloaded and placed in the same folder for proper work.

You can use ImCurr in CLI mode by executing `icengine` with arguments:

`./icengine source_file destined_file password mode`

`mode` is a number varying from 0 to 5 that sets processing mode:

0 - single file encryption

1 - single file decryption

2 - folder encryption

3 - folder decryption

4 - file injection

5 - file ejection

#### Other platforms
- [Android](https://github.com/shoraii/ImCurrAE)
- [Bot](https://github.com/shoraii/ImCurrBot)
