# Array Convertor
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

## The Array Convertor module
Sometimes in your JScript code, you have to convert your arrays into [*safearrays*](https://learn.microsoft.com/en-us/windows/win32/api/oaidl/ns-oaidl-safearray) so you can pass them to certain functions. For example, [the `Write` method](https://learn.microsoft.com/en-us/office/client-developer/access/desktop-database-reference/write-method-ado) of the [`ADODB.Stream` object](https://learn.microsoft.com/en-us/office/client-developer/access/desktop-database-reference/stream-object-ado) accepts only *safearrays* of type `VT_UI1` rather than JScript arrays. So the following code would be an error:

```js
var data = [ 0xA8, 0x4B, 0xDC, 0x6B ];
var stream = CreateObject("ADODB.Stream");
stream.Open();
stream.Type = 1;
stream.Write(data);
stream.SaveToFile("file.dat");
stream.Close();
```

Unfortunately, JScript doesn't support creating and manipulating *safearrays* on its own, but this Array Convertor module does the job. To solve the problem, you can use this module like below to convert your JScript array into a *safearray* before passing it to the `Write` method.

```js
var data = [ 0xA8, 0x4B, 0xDC, 0x6B ];
var ConvertArray = LoadStation("ArrayConvertor.dll");
var stream = CreateObject("ADODB.Stream");
stream.Open();
stream.Type = 1;
stream.Write(ConvertArray(data, "VT_UI1"));
stream.SaveToFile("file.dat");
stream.Close();
```

The following sections give further information on how to use the Array Convertor module.

### Loading the module
To load the module into your script, use the `LoadStation` function [as described in the Active Station documentation](https://github.com/javadbayat/ActiveStation/blob/main/docs/writing-client-script.md). Pass it the relative path of the module file, as usual. Then `LoadStation` will return a Function-like object that you can "call" to convert your arrays. Here's an example:

```js
var ConvertArray = LoadStation("ArrayConvertor.dll");
```

After that, you can assume the variable `ConvertArray` were rather a "function". And you can call it in the following 3 ways.

### To convert a JScript array into a *safearray*
To convert a JScript array into a *safearray*, call `ConvertArray` using the following syntax:

```js
safearray = ConvertArray( jsArray, baseType );
```

#### Parameters
+ `jsArray`: Set to the JScript array that is to be converted. This can be an `Array` object created using either the `new Array(...)` or `[ ... ]` constructs.
+ `baseType`: Optional. Set to the base type of the target *safearray*. Any of the elements in `jsArray` whose type doesn't match this base type will be converted to the base type before they are assigned to the resultant *safearray*. Specify this base type either as a numeric value from the [`VARENUM` enumeration](https://learn.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum), or as a string representing the name of one of the `VARENUM` constants (e.g `8` or `"VT_BSTR"`). If omitted, this parameter defaults to **VT_VARIANT (12)**.

#### Return Value
Returns the *safearray* resulting from the conversion. Note that unless `baseType` is set to **VT_VARIANT (12)**, you may not be able to manipulate the returned *safearray* directly from your JScript/VBScript code.

#### Example

```js
// After conversion, the integer element 325 will become the string "325" within the safearray
jsa = [ "Mike", "Jacob", 325, "David" ];

safearray = ConvertArray( jsa, "VT_BSTR" );
// Is equivalent to
safearray = ConvertArray( jsa, 8 );
```

### To convert a *safearray* into a JScript array
To convert a *safearray* into a JScript array, call `ConvertArray` using the following syntax:

```js
jsArray = ConvertArray( safearray, [] );
```

#### Parameters
+ `safearray`: Set to the *safearray* that is to be converted. This *safearray* can be of any base type.
+ The second parameter must be always set to an empty JScript array (`[]`). The reason for supplying this parameter is that the implementation of the Array Convertor module will extract the elements of the source *safearray* and then call the `push` method on this empty JScript array repeatedly to add each of the elements extracted. The Array Convertor module itself has no way to construct an empty JScript array, so it needs to take one from the caller, fill it with the elements taken from the source *safearray*, and finally return the same JS array that was passed in.

#### Return Value
Returns the JScript array resulting from the conversion.

### To change the base type of a *safearray*
To change the base type of a *safearray*, that is, to convert a *safearray* of one base type to another, call `ConvertArray` using the following syntax:

```js
safearray = ConvertArray( srcSafearray, baseType );
```

#### Parameters
+ `srcSafearray`: Set to the *safearray* that is to be converted. This *safearray* can be of any base type.
+ `baseType`: Optional. Set to the base type of the target *safearray*. All elements of `srcSafearray` will be converted to this base type before they are assigned to the resultant *safearray*. Specify this base type either as a numeric value from the [`VARENUM` enumeration](https://learn.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum), or as a string representing the name of one of the `VARENUM` constants (e.g `8` or `"VT_BSTR"`). If omitted, this parameter defaults to **VT_VARIANT (12)**.

#### Return Value
Returns the *safearray* resulting from the conversion. Note that unless `baseType` is set to **VT_VARIANT (12)**, you may not be able to manipulate the returned *safearray* directly from your JScript/VBScript code.
