#include "SummatorsVectorClass.h"


void SummatorsVector::Add(int64_t defaultvalue)
{
	if (ptr_table == nullptr) return;

	std::lock_guard<std::mutex> lock(lock_mutex);

	std::unique_ptr<Summator> newSummator = std::make_unique<Summator>();
	int row = ptr_table->rowCount();
	ptr_table->insertRow(row);
	ptr_table->setItem(row, 0, new QTableWidgetItem(QString::number(newSummator->GetSumm())));

	newSummator->SetRow(row);
	newSummator->SetTable(ptr_table);
	newSummator->SetSumm(defaultvalue);

	QObject::connect(newSummator.get(), &Summator::summChanged, newSummator.get(), &Summator::UpdateData, Qt::QueuedConnection);

	summators.push_back(std::move(newSummator));
}

void SummatorsVector::SetPtrTable(QTableWidget* table)
{
	ptr_table = table;
}

void SummatorsVector::Remove(int index)
{
	std::lock_guard<std::mutex> lock(lock_mutex);

	if (index < 0 || index >= summators.size()) return;
	int row = summators[index]->GetRow();
	if (row != summators.size() - 1)
	{
		std::swap(summators[index], summators.back());
		summators[index]->SetRow(row);
	}
	summators.pop_back();
}

void SummatorsVector::Increment()
{
	static auto prevTime = std::chrono::high_resolution_clock::now();
	static int64_t prevSumm = 0;

	std::lock_guard<std::mutex> lock(lock_mutex);
	
	int64_t newAllSumm = 0;

	for (const auto& item : summators)
	{
		if (item)
		{
			item->Increment();
			newAllSumm += item->GetSumm();
		}
	}

	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = currentTime - prevTime;

	if (deltaTime.count() >= 1.0)
	{
		double Hz = (newAllSumm - prevSumm) / deltaTime.count();
		emit FrequencyUpdate(Hz);

		prevSumm = newAllSumm;
		prevTime = currentTime;
	}
}

void SummatorsVector::ConnectToDB(const std::string& db_name)
{
	dataBase.connect(db_name);
	dataBase.Exec(CreatTableSQL);
}

void SummatorsVector::SaveDataToDB()
{
	std::lock_guard<std::mutex> lock(lock_mutex);

	std::vector<std::string> Param = {};
	
	std::string inserdata = InsertDataSQL;

	for (const auto& item : summators)
	{
		if (item)
		{
			Param.push_back(std::to_string(item->GetSumm()));
			inserdata += " (?),";
		}
	}
	inserdata.back() = ';';

	dataBase.Exec(DeleteDataSQL);
	dataBase.Exec(inserdata, Param);

}

void SummatorsVector::LoadDataToDB()
{
	SQLiteApi::ResultRows rows;
	

	rows = dataBase.Exec(ReadDataSQL);

	for (const auto& item : rows)
	{
		try
		{
			int64_t value = std::stoll(item.at(0));
			Add(value);
		}
		catch (...){}
	}
}
