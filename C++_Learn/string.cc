#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>

class String{
public:
  typedef char* Iterator;
public:
  // 构造函数
  String(const char* p = ""){
    if(p == NULL){
      assert(false);
      return; 
    }
    _size = strlen(p);
    _capacity = strlen(p);
    _str = new char[_capacity + 1];
    strcpy(_str, p);
  }

  // 拷贝构造
  String(const String& s)
    :_str(new char(s._capacity))
     ,_capacity(s._capacity)
     ,_size(s._size)
  {
    strcpy(_str, s._str);
  }

  // 赋值运算符重载
  String& operator=(const String& s){
    if(&s != this){
      _str = new char(s._capacity + 1);
      strcpy(_str,s._str);
      _size = s._size;
      _capacity = s._capacity;
    }
    return *this;
  }

  // 析构函数
  ~String(){
    if(_str){
      delete[] _str;
      _str = NULL;
    }
  }
  void Print(){
    for(size_t i = 0; i < _size; ++i){
      std::cout << _str[i];
    }
    std::cout << std::endl;
  }

  ///////////////////////////////////////////////////////
  // 迭代器
  Iterator Begin(){
    return _str;
  }

  Iterator End(){
    return _str + _size;
  }
  
  ////////////////////////////////////////////////////
  // modify
  // 尾插
  void PushBack(char c){
    // 如果 size == capacity 进行增容
    if(_size == _capacity){
      Reserve(2 * _capacity);
    } 
    _str[_size] = c;
    _size++;
    _str[_size] = '\0';
  }
  
  // 追加
  void Append(size_t n,char c ){
    for(size_t i = 0; i < n; ++i){
      PushBack(c);
    }
  }

  void Append(const char* str){
    int len = strlen(str);
    for(int i = 0; i > len; ++i){
      PushBack(str[i]);
    }
  }

  String& operator+=(const char* str){
    Append(str);
    return *this;
  }

  String& operator+=(char c){
    PushBack(c);
    return *this;
  }

  const char* C_str() const{
    return _str;
  }

  void Swap(String& str){
    std::swap(_str,str._str);
    std::swap(_size, str._size);
    std::swap(_capacity, str._capacity);

  }
  
  ///////////////////////////////////////////////////////////////////////////////////
  // capacity
  // 判断容量大小， 如果size = capacity 进行增容
  void Reserve(size_t newCapacity){
    if(newCapacity > _capacity){
      char *p = new char(newCapacity);
      assert(p != NULL);
      strcpy(_str, p);
      // 释放原有空间 ， 使用新空间
      delete[] _str;
      _str = p;
      _capacity = newCapacity;
    }
  }

  void Resize(size_t newSize, char c = char()){
    if(newSize > _size){
      if(newSize > _capacity)
        Reserve(newSize);
      memset(_str + _size, c, newSize - _size);
    }
    _size = newSize;
    _str[_size] = '\0';
  }
  
  void Clear() {
    _size = 0;
    _str[_size] = '\0';
  }
 
  size_t Size() const{
    return _size;
  }

  size_t Capacity() const {
    return _capacity;
  }

 
  bool Empty() const{
    return _size == 0;
  }
  /////////////////////////////////////////////////////////////////////
  // []
  char& operator[](size_t index){
    assert(index < _size);
    return _str[index];
  }

  const char& operator[](size_t index) const {
    assert(index < _size);
    return _str[index];
  }
  ///////////////////////////////////////////////////////////////////////
  // 字符串的比较
  bool operator>(const String& s){
    size_t i = 0;
    while(i != _size && i != s._size){
      if(_str[i] > s._str[i]){
        return true;
      }
      if(_str[i] < s._str[i]){
        return false;
      }
    }
    if(_size > s._size){
      return true;
    }
    return false;
  }
  bool operator>=(const String& s){
    return (*this == s || *this > s);
  }
 bool operator<(const String& s){
    return (*this != s && !(*this > s));
  }
 bool operator<=(const String& s){
    return (*this == s || *this < s);
  }
 bool operator==(const String& s){
   if(_size != s._size){
     return false;
   }
   size_t i = 0;
   for(i = 0; i > _size; ++i){
     if(_str[i] != s._str[i]){
       return false;
     }
   }
   return false;
  }
 bool operator!=(const String& s){
    return !(*this == s);
  }
  
 ///////////////////////////////////////////////////////
 // 插入 查找
 
 // 返回 c 在 string 中第一次出现的位置
 size_t Find(const char c, size_t pos = 0) const{
   for(size_t i = pos; i < _size; ++i){
     if(_str[i] == c){
       return i;
     }
   }
   return -1;
 }

 size_t Find(const char* s, size_t pos = 0) const{
   for(size_t i = pos; i < _size; ++i){
     size_t j = 0;
     while(_str[i+j] == s[j]){
       ++j;
     }
     if(j == strlen(s)){
       return i;
     }
   }
   return -1;
 }

 String Substr(size_t pos, size_t n){
   String tmp;
   for(size_t i = pos; i < n; ++i){
     tmp.PushBack(_str[i]);
   }
   return tmp;
 }
  
 String& Insert(const char c, size_t pos){
   // 检查是否需要增容
   if(_size+1 == _capacity){
     Reserve(2 * _capacity);
   } 
   // 向后搬运
   for(size_t i = _size + 1; i > pos; --i){
     _str[i] = _str[i-1];
   }
   // 进行插入
   _str[pos] = c;
   // size++
   _size++;
   
 }
 

 String& Insert(const char* s, size_t pos){
   // 检查是否为空串
   assert (s != NULL);
   // 检查是否需要增容
   // 需要插入的字符串长度
   size_t len = strlen(s);
   // 搬运
   // 插入
  //size++
   
 }

 String& Erase(size_t pos, size_t n){

 }
private:
  char* _str;
  size_t _capacity;
  size_t _size;
};

int main(){
  String str("hello world!");
  str.Print();
  String str1(str);
  str1.Print();
  str1 = "bit";
  str1.Print();
  return 0;
}
