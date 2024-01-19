// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) 2023 The Bitcoins Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINS_SCRIPT_BITCOINSCONSENSUS_H
#define BITCOINS_SCRIPT_BITCOINSCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_BITCOINS_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/bitcoins-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBBITCOINSCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BITCOINSCONSENSUS_API_VER 1

typedef enum bitcoinsconsensus_error_t
{
    bitcoinsconsensus_ERR_OK = 0,
    bitcoinsconsensus_ERR_TX_INDEX,
    bitcoinsconsensus_ERR_TX_SIZE_MISMATCH,
    bitcoinsconsensus_ERR_TX_DESERIALIZE,
    bitcoinsconsensus_ERR_AMOUNT_REQUIRED,
    bitcoinsconsensus_ERR_INVALID_FLAGS,
} bitcoinsconsensus_error;

/** Script verification flags */
enum
{
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_P2SH | bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | bitcoinsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int bitcoinsconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, bitcoinsconsensus_error* err);

EXPORT_SYMBOL int bitcoinsconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, bitcoinsconsensus_error* err);

EXPORT_SYMBOL unsigned int bitcoinsconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // BITCOINS_SCRIPT_BITCOINSCONSENSUS_H
