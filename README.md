# Hardened Crypto Algorithms in C (`crypto-algorithms-hardened`)

> **Maintained, Hardened Drop-in Fork of Brad Conte's Classic `B-Con/crypto-algorithms` Library**  
> *Audited, Patched, and Verified via DecodeIQ CodeTruth Engine*

[![License: Public Domain](https://img.shields.io/badge/License-Public%20Domain-blue.svg)](README.md)
[![Standards: NIST SP 800-38C / FIPS 197 / CERT-C](https://img.shields.io/badge/Standards-NIST%20SP%20800--38C%20%7C%20CERT--C-brightgreen.svg)]()
[![Status: Maintained](https://img.shields.io/badge/Status-Maintained%20Fork-orange.svg)]()

---

## 🛡️ Why This Fork Exists

`B-Con/crypto-algorithms` is one of the most popular lightweight C cryptographic collections on GitHub (~2,600+ stars), featuring clean implementations of **AES, Blowfish, DES/3DES, SHA-256, SHA-1, MD5, MD2, RC4, Base64, and ROT-13**.

However, the original repository has been unmaintained since **April 2015**. Over the last decade, changes in compiler optimizations (GCC 12+, Clang 15+) and modern cryptographic standards left several critical, silent vulnerabilities unaddressed:

1. **Critical AES-CCM Two-Time Pad Vulnerability:** A variable swap between `mac_len` and `nonce_len` froze the CTR counter to `0`, reusing key-streams across encrypted payloads.
2. **NIST SP 800-38C Non-Compliance:** Redundant 16-byte zero-block padding on exact-block associated data.
3. **C99 §6.5.7p4 Signed Shift Undefined Behavior:** Unsigned bytes promoted to `signed int` and shifted into bit 31 during AES key schedule generation.
4. **67 CERT-C EXP33 Uninitialized Stack Declarations:** Residual stack state in key schedules and cipher registers risking side-channel leakage.

---

## 🔧 What Was Fixed

* **100% Deterministic Remediation:** All 67 uninitialized variables across 10 modules initialized cleanly.
* **AES-CCM Counter Repaired:** Full alignment with NIST SP 800-38C Known Answer Tests.
* **UB Eliminated:** Safe unsigned 32-bit bitwise shifts.
* **100% ABI and Header Compatibility:** Drop-in replacement for `B-Con/crypto-algorithms`.
* **Full Forensic Report:** Read [`CRYPTO_ALGORITHMS_HARDENING_FORENSIC_REPORT.md`](CRYPTO_ALGORITHMS_HARDENING_FORENSIC_REPORT.md) for complete technical analysis.

---

## 🚀 Building & Running Tests

Compile with any standard C99+ compiler (GCC, Clang, MSVC):

```bash
# Compile and test AES
gcc -O2 aes.c aes_test.c -o test_aes && ./test_aes

# Compile and test SHA-256
gcc -O2 sha256.c sha256_test.c -o test_sha256 && ./test_sha256

# Compile and test Blowfish
gcc -O2 blowfish.c blowfish_test.c -o test_blowfish && ./test_blowfish
```

All 10 modules pass 100% of their test suites out of the box.

---

## 🦀 Safe Rust Alternative

Looking for a memory-safe, `#![forbid(unsafe_code)]` bare-metal alternative with zero heap allocations (`no_std`)?
Check out the **DecodeIQ Rust Verified Suite**:
👉 [`https://github.com/coboliqcom/tinycrypt-safe-rust`](https://github.com/coboliqcom/tinycrypt-safe-rust)
