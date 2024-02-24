Shared Libraries
================

## x1coinconsensus

The purpose of this library is to make the verification functionality that is critical to X1coin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `x1coinconsensus.h` located in `src/script/x1coinconsensus.h`.

#### Version

`x1coinconsensus_version` returns an `unsigned int` with the API version *(currently `1`)*.

#### Script Validation

`x1coinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `x1coinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/x1coin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/x1coin/bips/blob/master/bip-0066.mediawiki)) compliance
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/x1coin/bips/blob/master/bip-0147.mediawiki))
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/x1coin/bips/blob/master/bip-0065.mediawiki))
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/x1coin/bips/blob/master/bip-0112.mediawiki))
- `x1coinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/x1coin/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `x1coinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `x1coinconsensus_verify_script` for the verification status)*
- `x1coinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `x1coinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `x1coinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `x1coinconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used
- `x1coinconsensus_ERR_INVALID_FLAGS` - Script verification `flags` are invalid (i.e. not part of the libconsensus interface)

### Example Implementations
- [NX1coin](https://github.com/MetacoSA/NX1coin/blob/5e1055cd7c4186dee4227c344af8892aea54faec/NX1coin/Script.cs#L979-#L1031) (.NET Bindings)
- [node-libx1coinconsensus](https://github.com/bitpay/node-libx1coinconsensus) (Node.js Bindings)
- [java-libx1coinconsensus](https://github.com/dexX7/java-libx1coinconsensus) (Java Bindings)
- [x1coinconsensus-php](https://github.com/Bit-Wasp/x1coinconsensus-php) (PHP Bindings)
