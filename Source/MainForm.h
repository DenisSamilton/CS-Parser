#pragma once
#include "parser.h"
#include "devidefile.h"
//#include "ThreadRealTime.h"
#include "ThreadX.h"
#include <msclr\marshal_cppstd.h>
#include "ThreadRealTimeModeMainCycle.h"

namespace logparsercs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Runtime::InteropServices;
	using namespace System::IO;
    using namespace System::Threading;
	using namespace System::Threading::Tasks;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			Reflection::PropertyInfo ^pi = (dataGridView1->GetType())->GetProperty( "DoubleBuffered"
																								 , Reflection::BindingFlags::Instance
																								 | Reflection::BindingFlags::NonPublic );
			pi->SetValue( dataGridView1, true, nullptr );
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
		private: System::ComponentModel::IContainer^  components;
		protected:

		protected:

		protected:

     protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>

		private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

		private: System::Windows::Forms::StatusStrip^  statusStrip1;
		private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
		private: System::Windows::Forms::ToolStrip^  toolStrip1;
		private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
		private: System::Windows::Forms::ToolStripMenuItem^  importToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;







        private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
        private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
        private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox2;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
        private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
        private: System::Windows::Forms::CheckBox^  checkBox1;
		private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

		private: System::Windows::Forms::ToolTip^  toolTip1;
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox3;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		private: System::Windows::Forms::CheckBox^  checkBox2;






































































































        private: System::Windows::Forms::DataGridView^  dataGridView1;








		private: void StringToStlWString( System::String const ^ s, std::wstring & os )
			{
				String^ string = const_cast<String^>(s);
				const wchar_t* chars = reinterpret_cast<const wchar_t*>((Marshal::StringToHGlobalUni( string )).ToPointer());
				os = chars;
				Marshal::FreeHGlobal( IntPtr( (void*)chars ) );

			}

		private: System::String ^ StlWStringToString( std::wstring const & os )
			{
				String^ str = gcnew String( os.c_str() );
				//String^ str = gcnew String("");
				return str;
			}

		private: void SaveToCSV( DataGridView ^DGV, ToolStripProgressBar ^TSPB )
			{
				//String ^filename = gcnew String("");
				//SaveFileDialog ^sfd = gcnew SaveFileDialog();
				saveFileDialog1->Filter = "CSV (*.csv)|*.csv";
				saveFileDialog1->FileName = "Output.csv";
				if( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{
					//MessageBox::Show( "Data will be exported and you will be notified when it is ready." );
					if( File::Exists( saveFileDialog1->FileName ) )
					{
						try
						{
							File::Delete( saveFileDialog1->FileName );
						} catch ( IOException ^ex )
						{
							MessageBox::Show( "It wasn't possible to write the data to the disk.\r\n" + ex->Message, "Внимание!" );
                            return;
						}
					}
						
						int columnCount = DGV->ColumnCount;
						cli::array<String ^> ^output = gcnew cli::array<String ^>(DGV->RowCount + 1);

						TSPB->Maximum = output->Length;
						TSPB->Value = 1;
						for( int i = 0; i < columnCount; i++ )
						{
							if( DGV->Columns[i]->HeaderText->ToString()->TrimEnd( ';' )->Replace( ";", "," ) != nullptr )
								output[0] += DGV->Columns[i]->HeaderText->ToString()->TrimEnd( ';' )->Replace( ";", "," ) + ";";
						}
						output[0] += "\r\n";

						for( int i = 0; i < DGV->RowCount; i++ )
						{
							for( int j = 0; j < columnCount; j++ )
							{
								if( DGV->Rows[i]->Cells[j]->Value != nullptr )
									output[i+1] += DGV->Rows[i]->Cells[j]->Value->ToString()->TrimEnd( ';' )->Replace( ";", "," );
								output[i + 1] += ";";
							}
							//output[i+1] += "\r\n";
							TSPB->Value++;
						}
						File::WriteAllLines( saveFileDialog1->FileName, output, System::Text::Encoding::UTF8 );
                    TSPB->Value = 0;
					//MessageBox::Show( "Your file was generated and its ready for use." );
				}
			}

		Thread ^t;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager( MainForm::typeid ));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->importToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripTextBox3 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripTextBox2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip( this->components ));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->statusStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler( this, &MainForm::openFileDialog1_FileOk );
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"csv";
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size( 20, 20 );
			this->statusStrip1->Items->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 2 )
			{
				this->toolStripProgressBar1,
					this->toolStripStatusLabel1
			} );
			this->statusStrip1->Location = System::Drawing::Point( 0, 677 );
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->statusStrip1->Size = System::Drawing::Size( 1726, 29 );
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size( 1600, 23 );
			this->toolStripProgressBar1->Click += gcnew System::EventHandler( this, &MainForm::toolStripProgressBar1_Click );
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->ActiveLinkColor = System::Drawing::Color::Red;
			this->toolStripStatusLabel1->BackColor = System::Drawing::SystemColors::Control;
			this->toolStripStatusLabel1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size( 91, 24 );
			this->toolStripStatusLabel1->Text = L"error level: 0";
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size( 20, 20 );
			this->toolStrip1->Items->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 5 )
			{
				this->toolStripDropDownButton1,
					this->toolStripSeparator1, this->toolStripTextBox1, this->toolStripTextBox3, this->toolStripTextBox2
			} );
			this->toolStrip1->Location = System::Drawing::Point( 0, 0 );
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size( 1726, 27 );
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton1->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 2 )
			{
				this->importToolStripMenuItem,
					this->toolStripMenuItem1
			} );
			this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"toolStripDropDownButton1.Image" )));
			this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Size = System::Drawing::Size( 34, 24 );
			this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
			// 
			// importToolStripMenuItem
			// 
			this->importToolStripMenuItem->Name = L"importToolStripMenuItem";
			this->importToolStripMenuItem->Size = System::Drawing::Size( 257, 26 );
			this->importToolStripMenuItem->Text = L"Import LogFile (Ctr+O)";
			this->importToolStripMenuItem->Click += gcnew System::EventHandler( this, &MainForm::importToolStripMenuItem_Click );
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size( 257, 26 );
			this->toolStripMenuItem1->Text = L"Export LogFile as... (Ctr+S)";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler( this, &MainForm::toolStripMenuItem1_Click );
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size( 6, 27 );
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->BackColor = System::Drawing::SystemColors::Info;
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size( 60, 27 );
			this->toolStripTextBox1->Text = L"1000";
			this->toolStripTextBox1->ToolTipText = L"Максимальное к-ство символов в одной строке лога.";
			// 
			// toolStripTextBox3
			// 
			this->toolStripTextBox3->BackColor = System::Drawing::SystemColors::Info;
			this->toolStripTextBox3->Name = L"toolStripTextBox3";
			this->toolStripTextBox3->Size = System::Drawing::Size( 60, 27 );
			this->toolStripTextBox3->Text = L"48";
			this->toolStripTextBox3->ToolTipText = L"период времени в котором программа будет искать соответствующие события поднесени"
				L"я без прохода";
				// 
				// toolStripTextBox2
				// 
			this->toolStripTextBox2->BackColor = System::Drawing::SystemColors::Info;
			this->toolStripTextBox2->Name = L"toolStripTextBox2";
			this->toolStripTextBox2->Size = System::Drawing::Size( 60, 27 );
			this->toolStripTextBox2->Text = L"1";
			this->toolStripTextBox2->ToolTipText = L"К-ство потоков. (Файл разбивается на n частей и каждая обрабатывается отдельно)";
			this->toolStripTextBox2->Click += gcnew System::EventHandler( this, &MainForm::toolStripTextBox2_Click );
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
																																											 | System::Windows::Forms::AnchorStyles::Left)
																																											 | System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange( gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >( 7 )
			{
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7
			} );
			this->dataGridView1->Location = System::Drawing::Point( 0, 30 );
			this->dataGridView1->Name = L"dataGridView1";
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			this->dataGridView1->RowsDefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->RowTemplate->DefaultCellStyle->BackColor = System::Drawing::Color::White;
			this->dataGridView1->Size = System::Drawing::Size( 1726, 644 );
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->Tag = L"";
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler( this, &MainForm::dataGridView1_CellContentClick );
			// 
			// Column1
			// 
			this->Column1->Frozen = true;
			this->Column1->HeaderText = L"Время";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 140;
			// 
			// Column2
			// 
			this->Column2->Frozen = true;
			this->Column2->HeaderText = L"Номер пропуска HEX/DEC";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 120;
			// 
			// Column3
			// 
			this->Column3->Frozen = true;
			this->Column3->HeaderText = L"Иденти фикатор источника события";
			this->Column3->Name = L"Column3";
			this->Column3->Width = 75;
			// 
			// Column4
			// 
			this->Column4->Frozen = true;
			this->Column4->HeaderText = L"Идентификатор подчиненного устройства";
			this->Column4->Name = L"Column4";
			// 
			// Column5
			// 
			this->Column5->Frozen = true;
			this->Column5->HeaderText = L"Описание события";
			this->Column5->Name = L"Column5";
			this->Column5->Width = 300;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Номер считывателя подчиненного устройства";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 75;
			// 
			// Column7
			// 
			this->Column7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column7->HeaderText = L"Фрагмент лога";
			this->Column7->Name = L"Column7";
			this->Column7->Width = 3000;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point( 249, 6 );
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size( 109, 21 );
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = L"Мониторинг";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler( this, &MainForm::checkBox1_CheckedChanged );
			// 
			// button1
			// 
			this->button1->AllowDrop = true;
			this->button1->AutoEllipsis = true;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point( 1614, 3 );
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size( 100, 24 );
			this->button1->TabIndex = 4;
			this->button1->Tag = L"Если надоело ждать ткни ὑD ";
			this->button1->Text = L"Отмена";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler( this, &MainForm::button1_Click );
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
																																										 | System::Windows::Forms::AnchorStyles::Left)
																																										 | System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"pictureBox1.Image" )));
			this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"pictureBox1.InitialImage" )));
			this->pictureBox1->Location = System::Drawing::Point( 57, 152 );
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size( 100, 100 );
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Enabled = false;
			this->checkBox2->Location = System::Drawing::Point( 364, 6 );
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size( 99, 21 );
			this->checkBox2->TabIndex = 6;
			this->checkBox2->Text = L"Скроллинг";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size( 1726, 706 );
			this->Controls->Add( this->checkBox2 );
			this->Controls->Add( this->pictureBox1 );
			this->Controls->Add( this->button1 );
			this->Controls->Add( this->checkBox1 );
			this->Controls->Add( this->dataGridView1 );
			this->Controls->Add( this->toolStrip1 );
			this->Controls->Add( this->statusStrip1 );
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject( L"$this.Icon" )));
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LogParser (System utility)";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler( this, &MainForm::MainForm_FormClosing );
			this->Load += gcnew System::EventHandler( this, &MainForm::MainForm_Load );
			this->SizeChanged += gcnew System::EventHandler( this, &MainForm::MainForm_SizeChanged );
			this->Click += gcnew System::EventHandler( this, &MainForm::MainForm_Click );
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler( this, &MainForm::CtrS_Click );
			this->statusStrip1->ResumeLayout( false );
			this->statusStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout( false );
			this->toolStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout( false );
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void MainForm_Load( System::Object^  sender, System::EventArgs^  e )
			{ toolTip1->SetToolTip(this->button1, "Если надоело ждать ткни сюда" ); }
		private: System::Void MainForm_Click( System::Object^  sender, System::EventArgs^  e )
		{	}
		private: System::Void toolStripStatusLabel1_Click( System::Object^  sender, System::EventArgs^  e )
		{ }
		private: System::Void toolStripComboBox1_Click( System::Object^  sender, System::EventArgs^  e )
		{ }
	private: System::Void toolStripSeparator1_Click( System::Object^  sender, System::EventArgs^  e )
	{ }
	private: System::Void toolStripMenuItem1_Click( System::Object^  sender, System::EventArgs^  e )
	{
		SaveToCSV( dataGridView1, toolStripProgressBar1 );
	}

	private: int maxStrLength, maxThreadsGlobal, maxTimeBetweenEvents;
	private: std::wstring *filePath_copy;
	private: array< ThreadX^ > ^parsObjects = nullptr;
	private: array< Thread^ > ^threads = nullptr;
	private: size_t *reportSize = nullptr;
	private: std::wstring *pathToTmpFiles = nullptr;
	private: bool interrupt = false;
	private: bool doWork = false;

	private: System::Void importToolStripMenuItem_Click( System::Object^  sender, System::EventArgs^  e )
	{
		this->button1->Enabled = true;
		this->button1->PerformClick();
		this->button1->Enabled = false;
		this->pictureBox1->Enabled = false;
		this->pictureBox1->Visible = false;
		this->checkBox1->Enabled = false;	
		this->toolStrip1->Enabled = false;
		toolStripStatusLabel1->Text = "error level: 0";
		toolStripStatusLabel1->ForeColor = System::Drawing::SystemColors::ControlText;
        try{ 
            if(!Int32::TryParse( toolStripTextBox1->Text, maxStrLength ))throw gcnew Exception("Должно быть число!");
            if(!Int32::TryParse( toolStripTextBox2->Text, maxThreadsGlobal ))throw gcnew Exception( "Должно быть число!" );
						if(!Int32::TryParse( toolStripTextBox3->Text, maxTimeBetweenEvents ))throw gcnew Exception( "Должно быть число!" );
        } catch( Exception ^ex)
        {
            MessageBox::Show( "Введите правильные данные!", "Предупреждение.", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information );
            return;
        }//MessageBox::Show( ""+maxStrLength+maxThreads
				maxThreadsGlobal = maxThreadsGlobal > 0 ? maxThreadsGlobal : 1;

		try
		{
			openFileDialog1->InitialDirectory = ".\\";
			openFileDialog1->Filter = "LOG (*.log)|*.log|TXT (*.txt)|*.txt|ALL (*.*)|*.*";
			if( openFileDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK )
			{
				button1->Enabled = true;
				button1->PerformClick();
				//MessageBox::Show( "File has not been chosen!","Предупреждение", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information );
				return;
			}
			// Path to File...
			this->Text = String::Format( "LogParser (System utility) [{0}]", openFileDialog1->FileName );
			std::wstring filePath;
			StringToStlWString( openFileDialog1->FileName, filePath  );

			this->Cursor = Cursors::WaitCursor;
			
			//############################################### Real Time ###################################################################
      if( checkBox1->CheckState == CheckState::Checked ){
				dataGridView1->ScrollBars = ScrollBars::None;
				this->button1->Enabled = true;
				ThreadRealTimeMode ^ReadToEnd = gcnew ThreadRealTimeMode( filePath, maxStrLength, dataGridView1, checkBox2, maxTimeBetweenEvents );
				t = gcnew Thread( gcnew ThreadStart( ReadToEnd, &ThreadRealTimeMode::ThreadEntryPoint ) );
				t->Start();
				return;
			}
			//############################################### Real Time ###################################################################
			

			for( size_t i = 0; i < 80; i++ )
				dataGridView1->Rows->Add( "","","","","","","" );
			dataGridView1->Rows->Clear();
			this->pictureBox1->Enabled = true;
			this->pictureBox1->Visible = true;

			interrupt = false;
			doWork = true;
			filePath_copy = new std::wstring(filePath);
			backgroundWorker1->DoWork += gcnew DoWorkEventHandler( this, &logparsercs::MainForm::backgroundWorker1_DoWork );
			backgroundWorker1->RunWorkerAsync( );

		} catch( Exception ^ex )
		{
			MessageBox::Show( "" + ex,
												"Непредвиденная Ошибка",
												System::Windows::Forms::MessageBoxButtons::OK,
												System::Windows::Forms::MessageBoxIcon::Information );
		}
	}


	private: System::Void backgroundWorker1_DoWork( Object^ sender, System::ComponentModel::DoWorkEventArgs^ e )
	{
		try
		{
			if( !doWork ) return;
			doWork = false;
			this->pictureBox1->Enabled = true;
			this->pictureBox1->Visible = true;
			//Делим файл на maxThreads части , если файл больше 6877000b, если меньше, то maxThreads = 1.
			Devide DevideFile;
			int maxThreads = maxThreadsGlobal;
			std::wstring filePath(*filePath_copy);
			pathToTmpFiles = DevideFile.DevideFiles( filePath, maxThreads, maxStrLength );
			maxThreadsGlobal = maxThreads;
			if( pathToTmpFiles == nullptr )
				throw gcnew Exception( "\n\nCan't divide log for multithreading.\n" );

			this->button1->Enabled = true;
			reportSize = new size_t[maxThreads];

			//New Thread for generating report
			parsObjects = gcnew array< ThreadX^ >( maxThreads );
			threads = gcnew array< Thread^ >( maxThreads );


			//#################################################Start Threading########################################################
			for( int i = 0; i < maxThreads - 1; i++ )
			{
				parsObjects[i] = gcnew ThreadX( pathToTmpFiles[i], &reportSize[i], maxStrLength, maxTimeBetweenEvents, true );
				threads[i] = gcnew Thread( gcnew ThreadStart( parsObjects[i], &ThreadX::ThreadEntryPoint ) );
				threads[i]->Start();
			}
			parsObjects[maxThreads - 1] = gcnew ThreadX( pathToTmpFiles[maxThreads - 1], &reportSize[maxThreads - 1], maxStrLength, maxTimeBetweenEvents, true );
			threads[maxThreads - 1] = gcnew Thread( gcnew ThreadStart( parsObjects[maxThreads - 1], &ThreadX::ThreadEntryPoint ) );
			threads[maxThreads - 1]->Start();
			//########################################################################################################################

			for( int i = 0; i < maxThreads; i++ )
				threads[i]->Join();

			if( interrupt ) return;
			button1->Enabled = false;

			int errLevel = 0;
			bool ind = true;

			size_t sum = 0;
			for( int i = 0; i < maxThreads; i++ )
				sum += reportSize[i];

			dataGridView1->ScrollBars = ScrollBars::None;
			this->dataGridView1->AllowUserToOrderColumns = false;
			//dataGridView1->SuspendLayout();

			toolStripProgressBar1->Maximum = sum;
			toolStripProgressBar1->Value = 0;
			this->pictureBox1->Enabled = false;
			this->pictureBox1->Visible = false;

			for( int i = 0; i < maxThreads; i++ )
			{

				for( size_t j = 0; j < reportSize[i]; j++ )
				{

					std::vector<std::wstring> s = parsObjects[i]->Report->at( j );
						
					if( StlWStringToString( s[0] ) == L"0/100/0 0:0:0.0" )
					{
						if( ind )
							dataGridView1->RowTemplate->DefaultCellStyle->BackColor = System::Drawing::Color::White, ind = false;
						else
							dataGridView1->RowTemplate->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray, ind = true;
						dataGridView1->Rows->Add( 1 );
					} else
					{
						dataGridView1->Rows->Add( StlWStringToString( s[0] ),
																			StlWStringToString( s[1] ),
																			StlWStringToString( s[2] ),
																			StlWStringToString( s[3] ),
																			StlWStringToString( s[5] ),
																			StlWStringToString( s[4] ),
																			StlWStringToString( s[6] ) );
					}

					toolStripProgressBar1->Value++;
				}

				errLevel += parsObjects[i]->errorlevel;
				parsObjects[i]->FreePars();
			}

			this->checkBox1->Enabled = true;
			this->toolStrip1->Enabled = true;
			toolStripProgressBar1->Value = 0;
			this->dataGridView1->AllowUserToOrderColumns = true;
			dataGridView1->ScrollBars = ScrollBars::Both;
			//dataGridView1->ResumeLayout();
			//dataGridView1->Refresh();
			//dataGridView1->Update();
			//dataGridView1->AutoResizeRows();
			//dataGridView1->Select();
			//MainForm::Update();

			if( errLevel > 0 )
			{
				toolStripStatusLabel1->ForeColor = System::Drawing::Color::Red;
				toolStripStatusLabel1->Text = "error level: " + errLevel.ToString();
			} else toolStripStatusLabel1->ForeColor = System::Drawing::SystemColors::ControlText;

			this->Cursor = Cursors::Default;

			for( int i = 0; i < maxThreads && maxThreads > 1; i++ )
			{
				try
				{
					if( IO::File::Exists( StlWStringToString( pathToTmpFiles[i] ) ) )
						IO::File::Delete( StlWStringToString( pathToTmpFiles[i] ) );
				} catch( Exception ^ex )
				{
					MessageBox::Show( "Невозможно удалить временный файл \"" + StlWStringToString( pathToTmpFiles[i] ) + "\"\n" + ex,
														"Предупреждение",
														System::Windows::Forms::MessageBoxButtons::OK,
														System::Windows::Forms::MessageBoxIcon::Information );
				}
			}

			if( reportSize != nullptr ) delete[] reportSize;
			if( reportSize != nullptr ) delete[] pathToTmpFiles;

		} catch( Exception ^ex )
		{
			if( dynamic_cast< ThreadAbortException ^>(ex) == nullptr ) //Если поток прирвался, то НЕ выводим сообщ
				MessageBox::Show( "" + ex,
													"Непредвиденная Ошибка",
													System::Windows::Forms::MessageBoxButtons::OK,
													System::Windows::Forms::MessageBoxIcon::Information );
		}
	}

	private: System::Void openFileDialog1_FileOk( System::Object^  sender, System::ComponentModel::CancelEventArgs^  e )
	{ }
	private: System::Void dataGridView1_CellContentClick( System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e )
	{}
	private: System::Void toolStripProgressBar1_Click( System::Object^  sender, System::EventArgs^  e )
	{ }
	private: System::Void CtrS_Click( System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e )
	{ 
		if( e->Control && e->KeyCode == Keys::S )       // Ctrl-S Save
			toolStripMenuItem1->PerformClick();
        else if ( e->Control && e->KeyCode == Keys::O )// Ctrl-O Save
            importToolStripMenuItem->PerformClick();
        else if( e->KeyCode == Keys::Escape ){
					button1->PerformClick();
				}
	}
  private: System::Void MainForm_SizeChanged( System::Object^  sender, System::EventArgs^  e )
    {
        this->dataGridView1->Width = this->Width-15;
        this->dataGridView1->Height = this->Height-100;
				this->button1->Location = System::Drawing::Point( this->Width - 130, 3 );
        this->toolStripProgressBar1->Size = System::Drawing::Size( this->Width - 145, 20 );
				this->Refresh();
    }

	private: System::Void checkBox1_CheckedChanged( System::Object^  sender, System::EventArgs^  e )
	{
		if( toolStripTextBox2->Enabled == true ){
			toolStripTextBox2->Text = "1";
			toolStripTextBox2->Enabled = false;
			checkBox2->Enabled = true;
		}
		else
		{
			toolStripTextBox2->Enabled = true;
			checkBox2->Enabled = false;
		}
	}
	private: System::Void toolStripTextBox2_Click( System::Object^  sender, System::EventArgs^  e )
	{
		
	}

	private: System::Void MainForm_FormClosing( System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e )
	{
		//Determine if text has changed in the textbox by comparing to original text.
		if( dataGridView1->RowCount > 1 )
		{
			// Display a MsgBox asking the user to save changes or abort.
			System::Windows::Forms::DialogResult dr = MessageBox::Show( "Хотите ли вы сохранить таблицу в CSV\nперед выходом?", this->Text,
												MessageBoxButtons::YesNoCancel );
			if( dr == System::Windows::Forms::DialogResult::Yes )
			{
				// Cancel the Closing event from closing the form.
				//e->Cancel = true;
				SaveToCSV( dataGridView1, toolStripProgressBar1 );
			} else if( dr == System::Windows::Forms::DialogResult::Cancel )
			{
				e->Cancel = true;
				return;
			}
		}

			if( threads != nullptr )
				for( int i = 0; i < maxThreadsGlobal; i++ )
					if( threads[i] != nullptr )
						threads[i]->Abort();
			interrupt = true;

			if( t != nullptr )
				t->Abort();

			this->Cursor = Cursors::Default;
			this->pictureBox1->Enabled = false;
			this->pictureBox1->Visible = false;
			this->button1->Enabled = false;
			this->checkBox1->Enabled = true;
			this->toolStrip1->Enabled = true;
		
	}


	private: System::Void button1_Click( System::Object^  sender, System::EventArgs^  e )
	{
		if( threads != nullptr )
			for( int i = 0; i < maxThreadsGlobal; i++ )
				if( threads[i] != nullptr ) 
					threads[i]->Abort();
		interrupt = true;
		//backgroundWorker1->CancelAsync();

		if( t != nullptr )
			t->Abort();

		dataGridView1->ScrollBars = ScrollBars::Both;
		this->Cursor = Cursors::Default;
		this->pictureBox1->Enabled = false;
		this->pictureBox1->Visible = false;
		this->button1->Enabled = false;
		this->checkBox1->Enabled = true;
		this->toolStrip1->Enabled = true;
	}
};
}
