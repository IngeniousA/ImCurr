# ImCurr
Simple tool to hide and recover messages in files, including file corruption and ressurection.

## 0.3 version release!
#### Changelog:
- **Cut** all features except file decryption/encryption
- Improved **file encryption**: now you must set the **password** to the encrypted file to protect it from hacking
- **Auto mode**. You don't have to remember the size of a segment if you turn on Auto Mode. Program will divide and shuffle segments automatically. However:
  a. You still need to remember encryption password
  b. You can't decrypt file without knowing segment size if it was encrypted in non-automatic mode.

Note. You can't decrypt files with ImCurr **0.3**, which were encrypted with ImCurr **0.2.1**

### What can I do in this application?
  1. ~~Hide a message in any type of file without data loss~~
  2. ~~Recover a hidden message~~
  3. Corrupt or ressurect a file, please **be careful** with this option.
  4. ~~Make a deep ASCII symbol analysis in a file.~~
  
  Everything which is ~~striked~~ was removed in **0.3** version
### How do I launch this application?
  1. Go [here](https://yadi.sk/d/GKfPkF_n3KdVrn?ncrnd=6934), then press "Download" button. (For 0.2.1 version: [here](https://yadi.sk/d/0fQ_Bkfg3HsDpj?ncrnd=6934))
  2. Launch "imc.exe"
### I came across an issue, what should I do?
  1. Write [here](https://github.com/IngeniousA/ImCurr/issues) about an issue, I'll check it out.
  
#### To sum up, I can recommend you to check out Java implementation of ImCurr [here](https://github.com/ActisDEV/imCurrJVM/releases), which was made by @ActisDEV.
