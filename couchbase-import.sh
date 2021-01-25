DATASET=$(pwd)/dataset
CLUSTER=localhost:8091
BUCKET=bucket
USERNAME=admin
PASSWORD=password

make clean all
mkdir "${DATASET}"
rm -f "${DATASET}/*"
./chBenchmark -csv -wh 1 -pa "${DATASET}"

function couchbase_import {
  local type="$1"
  local columns="$2"
  local key="$3"
  # add column name into tab delimited file
  (echo "${columns}|TYPE" && cat "${DATASET}/$type.tbl" | while read line; do echo "${line}|${type}"; done) > "${DATASET}/${type}.couchbase.tbl"
  # import tab delimited file
  cbimport csv --cluster "${CLUSTER}" --username "${USERNAME}" --password "${PASSWORD}" --bucket "${BUCKET}" --field-separator "|" --dataset "file://${DATASET}/${type}.couchbase.tbl" --generate-key "%TYPE%:%${key}%"
}

couchbase_import "CUSTOMER" "C_ID|C_D_ID|C_W_ID|C_FIRST|C_MIDDLE|C_LAST|C_STREET_1|C_STREET_2|C_CITY|C_STATE|C_ZIP|C_PHONE|C_SINCE|C_CREDIT|C_CREDIT_LIM|C_DISCOUNT|C_BALANCE|C_YTD_PAYMENT|C_PAYMENT_CNT|C_DELIVERY_CNT|C_DATA|C_N_NATIONKEY" "C_ID"
couchbase_import "DISTRICT" "D_ID|D_W_ID|D_NAME|D_STREET_1|D_STREET_2|D_CITY|D_STATE|D_ZIP|D_TAX|D_YTD|D_NEXT_O_ID" "D_ID"
couchbase_import "HISTORY" "H_C_ID|H_C_D_ID|H_C_W_ID|H_D_ID|H_W_ID|H_DATE|H_AMOUNT|H_DATA" "H_C_ID"
couchbase_import "ITEM" "I_ID|I_IM_ID|I_NAME|I_PRICE|I_DATA" "I_ID"
couchbase_import "NATION" "N_NATIONKEY|N_NAME|N_REGIONKEY|N_COMMENT" "N_NATIONKEY"
couchbase_import "NEWORDER" "NO_O_ID|NO_D_ID|NO_W_ID" "NO_O_ID"
couchbase_import "ORDER" "O_ID|O_D_ID|O_W_IDO_W_ID|O_C_ID|O_ENTRY_D|O_CARRIER_ID|O_OL_CNT|O_ALL_LOCAL" "O_ID"
couchbase_import "REGION" "R_REGIONKEY|R_NAME|R_COMMENT" "R_REGIONKEY"
couchbase_import "STOCK" "S_I_ID|S_W_ID|S_QUANTITY|S_DIST_01|S_DIST_02|S_DIST_03|S_DIST_04|S_DIST_05|S_DIST_06|S_DIST_07|S_DIST_08|S_DIST_09|S_DIST_10|S_YTD|S_ORDER_CNT|S_REMOTE_CNT|S_DATA|S_SU_SUPPKEY" "S_I_ID"
couchbase_import "SUPPLIER" "SU_SUPPKEY|SU_NAME|SU_ADDRESS|SU_NATIONKEY|SU_PHONE|SU_ACCTBAL|SU_COMMENT" "SU_SUPPKEY"
couchbase_import "WAREHOUSE" "W_ID|W_NAME|W_STREET_1|W_STREET_2|W_CITY|W_STATE|W_ZIP|W_TAX|W_YTD" "W_ID"