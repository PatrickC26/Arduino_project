
void long2array(long a, unsigned char* b){
  if (a >= 0){
    for (int i = 7 ; i >= 4 ; i--) {
      b[i] = a / _FF_pow[i-4];
    }
  }
  else{
    a *= -1;
    for (int i = 7 ; i >= 4 ; i--) {
      b[i] = a / _FF_pow[i-4];
      b[i] = 0xFF - int(b[i]);
    }
  }
}

// is the array the same
bool checkArrayIdentical(unsigned char a[], unsigned char b[]){
  for (int i = 0 ; i < 4 ; i++){
    if (a[i] != b[i])
      return false;
  }
  return true;
}

void make_array_indentical(unsigned char* a, unsigned char* b){
  a[4] = b[4];
  a[5] = b[5];
  a[6] = b[6];
  a[7] = b[7];
}



// hex to int
int hexTable (char inC){
  switch(inC){
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'A':
      return 10;
    case 'B':
      return 11;
    case 'C':
      return 12;
    case 'D':
      return 13;
    case 'E':
      return 14;
    case 'F':
      return 15;
    default:
      return -1;
  }
}
