bool checkArrayIdentical(unsigned char a[], unsigned char b[]){
  for (int i = 0 ; i < 4 ; i++){
    if (a[i] != b[i])
      return false;
  }
  return true;
}
