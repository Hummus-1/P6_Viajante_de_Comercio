#include "RandomString.h"

std::string generateRandomString(int n) {
	char alphabet[MAX] = {
  'a', 'b', 'c', 'd', 'e', 'f', 'g',
  'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u',
  'v', 'w', 'x', 'y', 'z'
  };

	std::string res = "";
	for (int i = 0; i < n; i++)
		res = res + alphabet[rand() % MAX];
	
	return res;
}
