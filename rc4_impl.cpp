#include <iostream>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

#define MAX_KEY 256

struct rc4_key {

  int S[MAX_KEY], T[MAX_KEY];

};

class RC4_impl {

public:

  void RC4(rc4_key* key, int message_length, int* message_data, int* out_data) {

    int i = 0, j = 0;
    for(int p = 0; p < message_length; p++) {

      i = (i + 1) % MAX_KEY;
      j = (j + key->S[i]) % MAX_KEY;
      int q = key->S[i];
      key->S[i] = key->S[j];
      key->S[j] = q;
      int t = (key->S[i] + key->S[j]) % MAX_KEY;
      out_data[p] = message_data[p]^key->S[t];

    }

  }

  void RC4_key(rc4_key* key, int key_length, int* key_data) {

    if(key_length <= MAX_KEY) {
      KSA(key, key_length, key_data);
    } else if(key_length > MAX_KEY) {
      KSA(key, MAX_KEY, key_data);
    }

    PRNG(key);

  }

private:

  void KSA(rc4_key* key, int key_length, int* key_data) {

    for(int i = 0; i < MAX_KEY; i++) {

      key->S[i] = i;
      key->T[i] = key_data[i % key_length];

    }

  }

  void PRNG(rc4_key* key) {

    int j = 0;
    for(int i = 0; i < MAX_KEY; i++) {

      j = (j + key->S[i] + key->T[i]) % MAX_KEY;
      int k = key->S[i];
      key->S[i] = key->S[j];
      key->S[j] = k;

    }

  }

};

int main() {

  time_t start, end;
  int plaintext[1];
  plaintext[0] = 0b11110000;
  int ciphertext[1];
  int key[8];

  for(int i = 0; i < 8; i++) {

    key[i] = 0xFF;

  }

  rc4_key rckey;

  RC4_impl rc4;

  rc4.RC4_key(&rckey, 8, key);
  rc4.RC4(&rckey, 1, plaintext, ciphertext);
  cout << "Encryption of " << bitset<8>(plaintext[0]).to_string() << ": " << bitset<8>(ciphertext[0]).to_string() << endl;

  plaintext[0] = ciphertext[0];
  ciphertext[0] = 0;

  rc4.RC4_key(&rckey, 8, key);
  rc4.RC4(&rckey, 1, plaintext, ciphertext);

  cout << "Decryption of " << bitset<8>(plaintext[0]).to_string() << ": " << bitset<8>(ciphertext[0]).to_string() << endl;

  plaintext[0] = 0b11110000;
  ciphertext[0] = 0;

  cout << "Key: FF FF FF FF FF FF FF FF" << endl;

  return 1;

}
