## READ ME BEFORE USING IT

input example:
`student:///home/junk_chuan/Desktop/drcom.py`

the string `student://` means you use the student protocol.

you can **only use the student protocol** because we are vegetable

we cannot recognize other protocols.


### student protocol design

#### the fourth layer
the type of the file

|type  |encode  |
|------|--------|
|.txt  |0000    |
|.html |0001    |
|.jpg  |0010    |
|.png  |0011    |
|.json |0100    |
|.mp3  |0101    |
|.mp4  |0110    |
|.xml  |0111    |
|.md   |1000    |


#### the third layer

| studentid | student or teacher     | grade      |
|-----------|------------------------|------------|
| 7bits * 4 | 1bit; 0:teacher; 1:stu | 3bits code |

| grade     | encode |
|-----------|--------|
| teacher   | 000    |
| freshman  | 001    |
| sophomore | 010    |
| junior    | 011    |
| senior    | 100    |
| graduate  | 101    |
| doctoral  | 110    |

e.g:

| 20174179    | student | junior |
|-------------|---------|--------|
| 20 17 41 79 | 1       | 011    |

#### the second layer

| slice number | max number |
|--------------|------------|
| 8bits        | 8bits      |

#### the first layer -- check

