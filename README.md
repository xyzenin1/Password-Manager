# Password Manager
Program that allows the user to save their password by inserting both the site name and the password they want to keep safe.

# Programming Language Used
I used C++ to develop this password manager program to experiment with storing data into text files, encrypting and decrypting them, and extracting what the user has inputted.

# How The Encryption Works
It uses a XOR type encryption, where it compares two values; if the master key value is the same as the value it is being compared to, it returns a 1, and if not, it returns a 0. For example, 'C' is 01100011 in binary, and if I had master key set to 5, which is 00000101, then the final result would be 01100110, which is 'f'.
