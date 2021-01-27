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

#include "Config.h"
#include "CsvGenerator.h"

using namespace std;

static string path(const string &file) {
  return Config::getInitialDbCreationPath() + "/" + file;
}

static char getDelimiter() {
  return '|';
}

CsvGenerator::CsvGenerator() {
  DataSource::init();
  warehouseStream.open(path("WAREHOUSE.tbl"));
  districtStream.open(path("DISTRICT.tbl"));
  customerStream.open(path("CUSTOMER.tbl"));
  historyStream.open(path("HISTORY.tbl"));
  neworderStream.open(path("NEWORDER.tbl"));
  orderStream.open(path("ORDER.tbl"));
  orderlineStream.open(path("ORDERLINE.tbl"));
  itemStream.open(path("ITEM.tbl"));
  stockStream.open(path("STOCK.tbl"));
  nationStream.open(path("NATION.tbl"));
  supplierStream.open(path("SUPPLIER.tbl"));
  regionStream.open(path("REGION.tbl"));
}

CsvGenerator::~CsvGenerator() {
  warehouseStream.close();
  districtStream.close();
  customerStream.close();
  historyStream.close();
  neworderStream.close();
  orderStream.close();
  orderlineStream.close();
  itemStream.close();
  stockStream.close();
  nationStream.close();
  supplierStream.close();
  regionStream.close();
}

bool CsvGenerator::generate() {
  for (int iId = 1; iId <= 100000; iId++) {
	generateItem(iId);
  }
  int oId;
  int olCount;
  string customerTime;
  string orderTime;
  for (int wId = 1; wId <= Config::getWarehouseCount(); wId++) {
	generateWarehouse(wId);
	for (int iId = 1; iId <= 100000; iId++) {
	  generateStock(iId, wId);
	}
	for (int dId = 1; dId <= 10; dId++) {
	  generateDistrict(dId, wId);
	  for (int cId = 1; cId <= 3000; cId++) {
		if (customerTime.empty()) {
		  customerTime = DataSource::getCurrentTimeString();
		}
		generateCustomer(cId, dId, wId, customerTime);
		generateHistory(cId, dId, wId);
		oId = DataSource::permute(cId, 1, 3000);
		olCount = DataSource::nextOderlineCount();
		orderTime = DataSource::getCurrentTimeString();
		generateOrder(oId, dId, wId, cId, olCount, orderTime);
		for (int olNumber = 1; olNumber <= olCount; olNumber++) {
		  generateOrderLine(oId, dId, wId, olNumber, orderTime);
		}
		if (oId > 2100) {
		  generateNewOrder(oId, dId, wId);
		}
	  }
	}
  }
  for (int rId = 0; rId < 5; rId++) {
	generateRegion(rId, DataSource::getRegion(rId));
  }
  for (int i = 0; i < 62; i++) {
	generateNation(DataSource::getNation(i));
  }
  for (int suId = 0; suId < 10000; suId++) {
	generateSupplier(suId);
  }
  return true;
}

void CsvGenerator::generateWarehouse(int &wId) {
  //W_STATE
  warehouseStream << wId << getDelimiter();
  //W_NAME
  DataSource::addAlphanumeric64(6, 10, warehouseStream, 1);
  //W_STREET_1
  DataSource::addAlphanumeric64(10, 20, warehouseStream, 1);
  //W_STREET_2
  DataSource::addAlphanumeric64(10, 20, warehouseStream, 1);
  //W_CITY
  DataSource::addAlphanumeric64(10, 20, warehouseStream, 1);
  //W_STATE
  DataSource::addAlphanumeric62(2, warehouseStream, 1);
  //W_ZIP
  DataSource::addWDCZip(warehouseStream, 1);
  //W_TAX
  DataSource::addDouble(0.0, 0.2, 4, warehouseStream, 1);
  //W_YTD
  warehouseStream << "300000.00";
  warehouseStream << endl;
}

void CsvGenerator::generateDistrict(int &dId, int &wId) {
  //D_ID
  districtStream << dId << getDelimiter();
  //D_W_ID
  districtStream << wId << getDelimiter();
  //D_NAME
  DataSource::addAlphanumeric64(6, 10, districtStream, 1);
  //D_STREET_1
  DataSource::addAlphanumeric64(10, 20, districtStream, 1);
  //D_STREET_2
  DataSource::addAlphanumeric64(10, 20, districtStream, 1);
  //D_CITY
  DataSource::addAlphanumeric64(10, 20, districtStream, 1);
  //D_STATE
  DataSource::addAlphanumeric62(2, districtStream, 1);
  //D_ZIP
  DataSource::addWDCZip(districtStream, 1);
  //D_TAX
  DataSource::addDouble(0.0, 0.2, 4, districtStream, 1);
  //D_YTD
  districtStream << "30000.00" << getDelimiter();
  //D_NEXT_O_ID
  districtStream << "3001";
  districtStream << endl;
}

void CsvGenerator::generateCustomer(int &cId, int &dId, int &wId, string &customerTime) {
  string cLast;
  if (cId <= 1000) {
	DataSource::genCLast(cId - 1, cLast);
  } else {
	DataSource::randomCLast(cLast);
  }
  string cState = DataSource::randomAlphanumeric62(2);
  //C_ID
  customerStream << cId << getDelimiter();
  //C_D_ID
  customerStream << dId << getDelimiter();
  //C_W_ID
  customerStream << wId << getDelimiter();
  //C_FIRST
  DataSource::addAlphanumeric64(8, 16, customerStream, 1);
  //C_MIDDLE
  customerStream << "OE" << getDelimiter();
  //C_LAST
  customerStream << cLast << getDelimiter();
  //C_STREET_1
  DataSource::addAlphanumeric64(10, 20, customerStream, 1);
  //C_STREET_2
  DataSource::addAlphanumeric64(10, 20, customerStream, 1);
  //C_CITY
  DataSource::addAlphanumeric64(10, 20, customerStream, 1);
  //C_STATE
  customerStream << cState << getDelimiter();
  //C_ZIP
  DataSource::addWDCZip(customerStream, 1);
  //C_PHONE
  DataSource::addNumeric(16, customerStream, 1);
  //C_SINCE - date/time given by the os when the CUSTOMER table was populated
  customerStream << customerTime << getDelimiter();
  //C_CREDIT
  customerStream << (DataSource::randomTrue(0.1) ? "BC" : "GC") << getDelimiter();
  //C_CREDIT_LIM
  customerStream << "50000.00" << getDelimiter();
  //C_DISCOUNT
  DataSource::addDouble(0.0, 0.5, 4, customerStream, 1);
  //C_BALANCE
  customerStream << "-10.00" << getDelimiter();
  //C_YTD_PAYMENT
  customerStream << "10.00" << getDelimiter();
  //C_PAYMENT_CNT
  customerStream << "1" << getDelimiter();
  //C_DELIVERY_CNT
  customerStream << "0" << getDelimiter();
  //C_DATA
  DataSource::addAlphanumeric64(300, 500, customerStream, 1);
  //C_N_NATIONKEY
  customerStream << (int)(cState.c_str())[0];
  customerStream << endl;
}

void CsvGenerator::generateHistory(int &cId, int &dId, int &wId) {
  //H_C_ID
  historyStream << cId << getDelimiter();
  //H_C_D_ID
  historyStream << dId << getDelimiter();
  //H_C_W_ID
  historyStream << wId << getDelimiter();
  //H_D_ID
  historyStream << dId << getDelimiter();
  //H_W_ID
  historyStream << wId << getDelimiter();
  //H_DATE - current date and time
  historyStream << DataSource::getCurrentTimeString() << getDelimiter();
  //H_AMOUNT
  historyStream << "10.00" << getDelimiter();
  //H_DATA
  DataSource::addAlphanumeric64(12, 24, historyStream, 0);
  historyStream << endl;
}

void CsvGenerator::generateNewOrder(int &oId, int &dId, int &wId) {
  //NO_O_ID
  neworderStream << oId << getDelimiter();
  //NO_D_ID
  neworderStream << dId << getDelimiter();
  //NO_W_ID
  neworderStream << wId;
  neworderStream << endl;
}

void CsvGenerator::generateOrder(int &oId, int &dId, int &wId, int &cId, int &olCount, string &orderTime) {
  //O_ID
  orderStream << oId << getDelimiter();
  //O_D_ID
  orderStream << dId << getDelimiter();
  //O_W_ID
  orderStream << wId << getDelimiter();
  //O_C_ID
  orderStream << cId << getDelimiter();
  //O_ENTRY_D - current date/ time given by the os
  orderStream << orderTime << getDelimiter();
  //O_CARRIER_ID - random within [1 .. 10] if O_ID <= 2100, null otherwise
  if (oId <= 2100) {
	DataSource::addInt(1, 10, orderStream, 1);
  } else {
	orderStream << "" << getDelimiter();
  }
  //O_OL_CNT
  orderStream << olCount << getDelimiter();
  //O_ALL_LOCAL
  orderStream << "1";
  orderStream << endl;
}

void CsvGenerator::generateOrderLine(int &oId, int &dId, int &wId, int &olNumber, string &orderTime) {
  //OL_O_ID
  orderlineStream << oId << getDelimiter();
  //OL_D_ID
  orderlineStream << dId << getDelimiter();
  //OL_W_ID
  orderlineStream << wId << getDelimiter();
  //OL_NUMBER
  orderlineStream << olNumber << getDelimiter();
  //OL_I_ID
  DataSource::addInt(1, 100000, orderlineStream, 1);
  //OL_SUPPLY_W_ID
  orderlineStream << wId << getDelimiter();
  //OL_DELIVERY_D = O_ENTRY_D if OL_O_ID <= 2100, null otherwise
  orderlineStream << (oId <= 2100 ? orderTime : "") << getDelimiter();
  //OL_QUANTITY
  orderlineStream << "5" << getDelimiter();
  //OL_AMOUNT = 0.00 if OL_O_ID <= 2100, random within [0.01..9999.99] otherwise
  if (oId <= 2100) {
	orderlineStream << "0.00" << getDelimiter();
  } else {
	DataSource::addDouble(0.01, 9999.99, 2, orderlineStream, 1);
  }
  //OL_DIST_INFO
  DataSource::addAlphanumeric64(24, orderlineStream, 0);
  orderlineStream << endl;
}

void CsvGenerator::generateItem(int &iId) {
  //I_ID
  itemStream << iId << getDelimiter();
  //I_IM_ID
  DataSource::addInt(1, 10000, itemStream, 1);
  //I_NAME
  DataSource::addAlphanumeric64(14, 24, itemStream, 1);
  //I_PRICE
  DataSource::addDouble(1.0, 100.0, 2, itemStream, 1);
  //I_DATA
  if (DataSource::randomTrue(0.1)) {
	DataSource::addAlphanumeric64Original(26, 50, itemStream, 0);
  } else {
	DataSource::addAlphanumeric64(26, 50, itemStream, 0);
  }
  itemStream << endl;
}

void CsvGenerator::generateStock(int &iId, int &wId) {
  //S_I_ID
  stockStream << iId << getDelimiter();
  //S_W_ID
  stockStream << wId << getDelimiter();
  //S_QUANTITY
  DataSource::addInt(10, 100, stockStream, 1);
  //S_DIST_01
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_02
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_03
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_04
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_05
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_06
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_07
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_08
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_09
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_DIST_10
  DataSource::addAlphanumeric64(24, stockStream, 1);
  //S_YTD
  stockStream << "0" << getDelimiter();
  //S_ORDER_CNT
  stockStream << "0" << getDelimiter();
  //S_REMOTE_CNT
  stockStream << "0" << getDelimiter();
  //S_DATA
  if (DataSource::randomTrue(0.1)) {
	DataSource::addAlphanumeric64Original(26, 50, stockStream, 1);
  } else {
	DataSource::addAlphanumeric64(26, 50, stockStream, 1);
  }
  //S_SU_SUPPKEY - no TPC-C/CH-benchmark spec
  stockStream << ((iId * wId) % 10000);
  stockStream << endl;
}

void CsvGenerator::generateNation(Nation n) {
  //N_NATIONKEY
  nationStream << n.id << getDelimiter();
  //N_NAME
  nationStream << n.name << getDelimiter();
  //N_REGIONKEY
  nationStream << n.rId << getDelimiter();
  //N_COMMENT
  DataSource::addTextString(31, 114, nationStream, 0);
  nationStream << endl;
}

void CsvGenerator::generateSupplier(int &suId) {
  //SU_SUPPKEY
  supplierStream << suId << getDelimiter();
  //SU_NAME
  supplierStream << "Supplier#" << DataSource::strLeadingZero(suId, 9) << getDelimiter();
  //SU_ADDRESS
  DataSource::addAlphanumeric64(10, 40, supplierStream, 1);
  //SU_NATIONKEY
  DataSource::addNId(supplierStream, 1);
  //SU_PHONE
  DataSource::addSuPhone(suId, supplierStream, 1);
  //SU_ACCTBAL
  DataSource::addDouble(-999.99, 9999.99, 2, supplierStream, 1);
  //SU_COMMENT 5 rows "Customer%Recommends" + 5 rows "Customer%Complaints"
  if ((suId + 7) % 1893 == 0) {
	DataSource::addTextStringCustomer(25, 100, "Complaints", supplierStream, 0);
  } else if ((suId + 13) % 1983 == 0) {
	DataSource::addTextStringCustomer(25, 100, "Recommends", supplierStream, 0);
  } else {
	DataSource::addTextString(25, 100, supplierStream, 0);
  }
  supplierStream << endl;
}

void CsvGenerator::generateRegion(int &rId, const char *rName) {
  //R_REGIONKEY
  regionStream << rId << getDelimiter();
  //R_NAME
  regionStream << rName << getDelimiter();
  //R_COMMENT
  DataSource::addTextString(31, 115, regionStream, 0);
  regionStream << endl;
}