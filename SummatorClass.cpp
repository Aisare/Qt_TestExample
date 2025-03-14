#include "SummatorClass.h"

void Summator::Increment()
{
	summ.fetch_add(1,std::memory_order_relaxed);
	emit summChanged(summ.load(std::memory_order_relaxed));
}

int64_t Summator::GetSumm()
{
	return summ.load(std::memory_order_relaxed);
}

void Summator::SetSumm(int64_t value)
{
	summ.store(value, std::memory_order_relaxed);
}

void Summator::SetRow(int newRow)
{
	rowTable = newRow;
}

void Summator::SetTable(QTableWidget* table)
{
	ptrTable = table;
}

void Summator::UpdateData(int newData)
{
	if (ptrTable == nullptr || rowTable < 0 || rowTable >= ptrTable->rowCount()) return;

	QTableWidgetItem* item = ptrTable->item(rowTable, 0);
	if (item)
		item->setText(QString::number(newData));
	else
		ptrTable->setItem(rowTable, 0, new QTableWidgetItem(QString::number(newData)));
}

int Summator::GetRow()
{
	return rowTable;
}

