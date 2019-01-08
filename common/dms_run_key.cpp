#include "dms_run_key.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "md5.h"
#include "debug_common.h"

class EntryHandler {
 public:
   virtual void Handle(const std::string &full_entry_name) = 0;
};

class NetWorkEntryHandler : public EntryHandler{
 public:
  virtual void Handle(const std::string &full_entry_name) {
    std::string address_name = full_entry_name + "/address";
    std::ifstream infile;
    infile.open(address_name.c_str());

    std::string mac_address;
    infile >> mac_address;

    //记录最小的MAC地址
    if (mac_address.empty() || mac_address == "00:00:00:00:00:00") {
      //无效mac地址
      return ;
    } 
    if (latest_mac_address_.empty() || 
        latest_mac_address_.compare(mac_address) > 0) {
      latest_mac_address_ = mac_address;
    }
  }

  std::string latest_mac_address_;
};

// all files under dir_name , do something on dir */
static void ForEachEntry(const std::string &dir_name, EntryHandler &entry_handler) {
  // check the parameter !
  if(dir_name.empty()) {
    std::cerr << " dir_name is empty! " << std::endl;
    return ;
  }

  // check if dir_name is a valid dir
  struct stat s;
  lstat(dir_name.c_str() , &s );
  if (!S_ISDIR(s.st_mode)) {
    std::cerr << "dir_name is not a valid directory !" << std::endl;
    return ;
  }

  struct dirent * dir_entry;    // return value for readdir()
  DIR * dir;                   // return value for opendir()
  dir = opendir(dir_name.c_str());
  if (NULL == dir) {
    std::cout << "Can not open dir " << dir_name << std::endl;
    return ;
  }

  // read all the files in the dir ~ 
  while((dir_entry = readdir(dir)) != NULL ) {
    // get rid of "." and ".."
    std::string dir_entry_name(dir_entry->d_name);
    if (dir_entry_name == "." || dir_entry_name == "..") {
      continue;
    }
    std::string full_entry_name = dir_name + "/" + dir_entry_name;
    entry_handler.Handle(full_entry_name);
  }
  closedir(dir);
} 

std::string DmsRunKey::Generate() {
  std::string handle_dir_name = "/sys/class/net/";
  NetWorkEntryHandler handler;
  //遍历网卡，寻找最小的有效地址
  ForEachEntry(handle_dir_name, handler);

  //生成RUN_KEY
  std::string run_key_ori = handler.latest_mac_address_ + "MINIEYE_DMS";
  MD5 md5_obj(run_key_ori);

  return md5_obj.toStr();
}

int DmsRunKey::Test(int argc, char *argv[]) {
  DmsRunKey drk;
  for (int i = 0; i < 1000; i++) {
    std::string run_key = drk.Generate();
    std::cout << "run key is " << run_key << std::endl;
  }
  return 0;
}

