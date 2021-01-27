/*
Copyright 2014 Florian Wolf, SAP AG

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef TUPLEGEN_H
#define TUPLEGEN_H

#include "DataSource.h"

#include <fstream>
#include <string>

using namespace std;

class CsvGenerator {
private:
  string datasetPath;

  ofstream warehouseStream;
  ofstream districtStream;
  ofstream customerStream;
  ofstream historyStream;
  ofstream neworderStream;
  ofstream orderStream;
  ofstream orderlineStream;
  ofstream itemStream;
  ofstream stockStream;
  ofstream nationStream;
  ofstream supplierStream;
  ofstream regionStream;

  void generateWarehouse(int &wId);

  void generateDistrict(int &dId, int &wId);

  void generateCustomer(int &cId, int &dId, int &wId, string &customerTime);

  void generateHistory(int &cId, int &dId, int &wId);

  void generateNewOrder(int &oId, int &dId, int &wId);

  void generateOrder(int &oId, int &dId, int &wId, int &cId, int &olCount, string &orderTime);

  void generateOrderLine(int &oId, int &dId, int &wId, int &olNumber, string &orderTime);

  void generateItem(int &iId);

  void generateStock(int &iId, int &wId);

  void generateNation(Nation n);

  void generateSupplier(int &suId);

  void generateRegion(int &rId, const char *rName);
public:
  CsvGenerator();

  ~CsvGenerator();

  bool generate();
};
#endif