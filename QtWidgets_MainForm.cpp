#include "QtWidgets_MainForm.h"



QtWidgets_MainForm::QtWidgets_MainForm(const std::string& pathDB, QWidget *parent)
	: QWidget(parent), DBName(pathDB)
{
	ui.setupUi(this);
    Initialization();
    LoadOnDB();
    StartThread();
}

QtWidgets_MainForm::~QtWidgets_MainForm()
{
    StopThread();
}

void QtWidgets_MainForm::Initialization()
{

    table = new QTableWidget(this);  
    table->setSelectionBehavior(QAbstractItemView::SelectRows); 
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setColumnCount(1);
    QObject::connect(table, &QTableWidget::itemSelectionChanged, this, &QtWidgets_MainForm::SelectedItem);

    label = new QLabel("0",this);

    QObject::connect(&summators, &SummatorsVector::FrequencyUpdate, this, &QtWidgets_MainForm::UpdateLabel);

    QPushButton* buttons[3] = { nullptr };
    
    buttons[0] = CreatButton("Add Summator", this, std::bind(&QtWidgets_MainForm::AddNewSummator,this));
    buttons[1] = CreatButton("Remove Summator", this, std::bind(&QtWidgets_MainForm::RemoveSelectedSummator,this));
    buttons[2] = CreatButton("Save on DataBase", this, std::bind(&QtWidgets_MainForm::SaveOnDB,this));
    
    
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();

    hLayout->addWidget(buttons[0]);
    hLayout->addWidget(buttons[1]);
    hLayout->addWidget(buttons[2]);
    hLayout->addStretch(); 

    vLayout->addWidget(table);  
    vLayout->addWidget(label);      
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    setLayout(vLayout);

    summators.SetPtrTable(table);
    summators.ConnectToDB(DBName);
}

void QtWidgets_MainForm::LoadOnDB()
{
    qDebug() << "LoadOnDB";
    summators.LoadDataToDB();
}

void QtWidgets_MainForm::SaveOnDB()
{
    qDebug() << "SaveOnDB";
    summators.SaveDataToDB();
}

void QtWidgets_MainForm::ThreadIncrement()
{
    qDebug() << "ThreadIncriment";
    while (!isExitFlag.load())
    {
        summators.Increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
        
}

void QtWidgets_MainForm::AddNewSummator()
{
    qDebug() << "AddNewSummator";
    summators.Add();
}

void QtWidgets_MainForm::RemoveSelectedSummator()
{
    qDebug() << "RemoveSelectedSummator";
    summators.Remove(selectedRow);
    table->removeRow(table->rowCount() - 1);
}

void QtWidgets_MainForm::SelectedItem()
{
    QList<QTableWidgetSelectionRange> selectedRanges = table->selectedRanges();
    if (!selectedRanges.isEmpty()) 
    {
        selectedRow = selectedRanges.first().topRow();
    }
}

void QtWidgets_MainForm::StartThread()
{
    qDebug() << "StartThread";
    IncrementThread = std::make_unique<std::thread>([&]() { this->ThreadIncrement(); });
    if (IncrementThread && IncrementThread->joinable())
    {
        qDebug() << "Thread successfully started!";
    }
    else 
    {
        qDebug() << "Failed to start thread!";
    }
}

void QtWidgets_MainForm::StopThread()
{
    qDebug() << "StopThread";
    isExitFlag.store(true);
    if (IncrementThread && IncrementThread->joinable())
    {
        IncrementThread->join();
    }
}

void QtWidgets_MainForm::UpdateLabel(double newHz)
{
    if (label == nullptr) return;
    label->setText(std::to_string(newHz).c_str());
}

QPushButton* QtWidgets_MainForm::CreatButton(const QString& buttonText, QWidget* parent, std::function<void()> onClickFunction)
{
    QPushButton* button = new QPushButton(buttonText, this);
    QObject::connect(button, &QPushButton::clicked, parent, [onClickFunction]() { onClickFunction(); });
    return button;
}
