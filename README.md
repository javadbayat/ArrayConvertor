# ArrayConvertor
A COM component (`ArrayConvertor.dll`) that enables you to convert Automation safe-arrays into JScript Array objects and vice-vesa, and also convert safe-arrays of one base type into another type. Plus, a simple encryption script (`Encryption.wsf`) that makes use of this COM component and encrypts a file with a key.

This program is based on the **Active Station** technology. Thus, to compile the source code of `ArrayConvertor.dll`, it is required that the static library files `libstation.x86.lib` and `libstation.x64.lib` be present in the project directory. To obtain these files, head to [the ActiveStation repository](https://github.com/javadbayat/ActiveStation), and compile the static library's source code from that repository.

## How to use the encryption script
To encrypt a file, start the `Encryption.wsf` script by opening **Command Prompt** and executing the following command:

```
cscript Encryption.wsf SourceFile DestFile
```

Where:

+ `SourceFile` is the name of the file that is to be encrypted.
+ `DestFile` is the file path where the resulting encrypted file is to be stored. If this parameter is omitted, the source file will be encrypted in place (that is, the source file will be overwritten with the resulting encrypted data).

These parameters can be **relative or absolute paths**. After the script starts, it will show **a dialog box asking you to enter the encryption key**.

Then, showing the following message will indicate success:

> Your file has been successfully encrypted!

Later, re-encrypting the encrypted file with the same key will produce the original file.
