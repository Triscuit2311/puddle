
## Puddle
The concept here is simple, we allocate more memory than we need to store some valuable data, and we obfuscate the data by hiding it in this block.
Before I explain further, please note there are no cryptographically secure methods here, and this is not reccomended for production use.

### How it works
All operations involving the data puddle are abstracted into anonymous lambdas, which adds a level of complexity to the assembly output.

On Set and Get, we dynamically determine the location of the data within the buffer. Currently the only option I have implemented is to store the data contiguously, but obfuscated.

During the set operation, we populate the buffer with random data byte by byte, until we reach the location which we intend to store the data, at which point we apply a XOR cipher as we write the memory to the buffer.
The result here is a buffer filled with seemingly random data, since to types are preserved and all the data is random, it would be difficult to reverse and infer types given a memory snapshot.
This also means that the offset to the data is not stored, it is calculated deterministically during access-time. (See snippet below)

During the get operation, the once again the data offset is calculated and the buffer accessed at that location, the bytes are decryped during set time. The get method takes an output reference where the bytes will be written.

Also provided are eq, neq, gt, gte, lt, and lte methods, all of which take one (or optionally two) std::function parameters. These methods are to aid in obfuscating logic, since the data comparison and the branches are executed in nested anonymous lambda function.

### Limitations
Many. 
Stashing objects with pointer values leaves validation up to the programmer, no checks or error handling is performed on logic operations. Lambda captures must be used with caution because of this.
Of course, using the get method on a puddle writes your data back into clear memory space, and should be avoided, prefer method comparisons if possible.
Reversing the algorithm for determining the offset of the memory in data is all that would be nessesary to gain full access to the memory, since the XOR cipher is also based on buffer location. See the Set snippet:

```cpp
unsigned int buff__offset = (unsigned int)(((uint64_t)this) % ((sizeof(T) * buff_sz_factor_) - 0x01 - sizeof(T)));

            // set all new bytes in buff_, set value bytes from input
            for(int i = 0; i < sizeof(T) * buff_sz_factor_; i++){
                if(i >= buff__offset && i < buff__offset + sizeof(T)){
                    buff_[i] = *(((char*)&val) + (i-buff__offset)) ^ ((buff__offset + i) % 0xff);
                    continue;
                }
                buff_[i] = rand() % (sizeof(T) * buff_sz_factor_);
            }
```

### Why?
Just a dabble.
