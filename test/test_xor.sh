echo "c2486f4796f0657481a655c559b38aaa" > test/message
cat test/message | ./mypgp -aes -c -b 6b50fd39f06d33cfefe6936430b6c94f > ciphered
cat ciphered
cat ciphered | ./mypgp -aes -d -b 6b50fd39f06d33cfefe6936430b6c94f