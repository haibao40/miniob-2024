//
// Created by lml on 2024/10/30.
//

#include "sql/operator/insert_with_tuples_physical_operator.h"
#include "sql/stmt/create_table_select_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

InsertTuplesPhysicalOperator::InsertTuplesPhysicalOperator(Table *table)
    : table_(table)
{}

RC InsertTuplesPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  // std::unique_ptr<PhysicalOperator> &child1 = children_[1];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    vector<Value> values;
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);

    //从1开始，是因为第0个位置是空值列表,这里把所有字段值保存起来
    for(int i = 0; i < row_tuple->cell_num(); i++) {
      Value value;
      row_tuple->cell_at(i, value);
      values.push_back(value);
    }

    //拿到value后存进列表，然后将value列表生成记录，最后用事务插入记录
    Record record;
    rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
    }

    rc = trx->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
        return rc;
    }
  }

  child->close();

  return RC::SUCCESS;
}

RC InsertTuplesPhysicalOperator::next() { return RC::RECORD_EOF; }

RC InsertTuplesPhysicalOperator::close() { return RC::SUCCESS; }