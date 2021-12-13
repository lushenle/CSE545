gpg --full-generate-key
gpg --import cse545_fall2021.asc
gpg --armor --output pubkey.asc --export 3C6B1D3DBCC59E27093F491E8A56A0679FE1E771
gpg --armor --output hacker.txt.asc.gpg --recipient D60CB02330E6F0DB74471B20CFECA88BAA7C9219 --encrypt hacker.txt.asc

