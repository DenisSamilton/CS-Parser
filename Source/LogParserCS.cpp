#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute()]
void Main( /*array<System::String ^> ^args*/	 )
{
 Application::EnableVisualStyles();
 Application::SetCompatibleTextRenderingDefault( false );
 Application::Run( gcnew logparsercs::MainForm() );
}