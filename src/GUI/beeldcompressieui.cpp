#include "beeldcompressieui.h"


BeeldCompressieUI::BeeldCompressieUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	
	// UI-elemente koppelen aan functies
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(open()));
	connect(ui.actionOpenAs, SIGNAL(triggered()), this, SLOT(openAs()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(save()));
	connect(ui.actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.spinQStart, SIGNAL(valueChanged(int)), this, SLOT(changeQStart(int)));
	connect(ui.spinQRaise, SIGNAL(valueChanged(int)), this, SLOT(changeQRaise(int)));
	connect(ui.spinBlocksize, SIGNAL(valueChanged(int)), this, SLOT(changeBlocksize(int)));
	connect(ui.actionCompress, SIGNAL(triggered()), this, SLOT(on_pushComprimeren_clicked()));

	m_View = NULL;
	item = NULL;
	currentBlocksize = 1;
	com = new Compression();
	com->setQStart(ui.spinQStart->value());
	com->setQRaise(ui.spinQRaise->value());
	com->setBlocksize(ui.spinBlocksize->value());
	decom = new Decompression();	
}

BeeldCompressieUI::~BeeldCompressieUI()
{
	delete com;
	delete decom;
}

/* *.raw file openen klaarmaken voor compressie + uittekenen */
void BeeldCompressieUI::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Bestand openen"), "/home/", tr("Raw-file (*.raw)"));
	if(fileName != ""){
		bool okHeight;
		bool okWidth;
		int height =  QInputDialog::getInteger ( this, "Give The Image Height", "Image Height: ", 512, 4, 65536, 4, &okHeight, Qt::Popup );
		if (!okHeight){
			QMessageBox::warning ( NULL, "Error - Wrong Height", "\nHeight is not ok, it must be a multiple of 4... \n");
			return;
		}
		int width =  QInputDialog::getInteger ( this, "Give The Image Width", "Image Width: ", 512, 4, 65536, 4, &okWidth, Qt::Popup );
		if (!okWidth){
			QMessageBox::warning ( NULL, "Error - Wrong Width", "\nWidth is not ok: it must be a power of 2... \n");
			return;
		}
		if (width > height)
			ui.spinBlocksize->setMaximum(height);
		else
			ui.spinBlocksize->setMaximum(width);
		ui.spinBlocksize->setValue(1);
		changeBlocksize(1);
		com->setHeight(height);
		com->setWidth(width);
		com->renewMatrix(); // matrix herinstellen met nieuwe hoogte en breedte
		updateHeight(height);
		updateWidth(width);
		com->setFile(fileName.toStdString());
		if (com->Read() == 0){
			QMessageBox::warning ( NULL, "Fout bij laden van bestand", "\nBestand niet gevonden... \n");
		}
		else{
			rawFile = fileName;
			drawImage(com->getMatrix(), com->getWidth(), com->getHeight(), ui.screen);
		}
	}
}

/* *.comp openen deze decompressen, vervolgens klaarmaken voor opnieuw te compressen + uittekenen */
void BeeldCompressieUI::openAs()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Bestand openen"), "/home/", tr("Compressed Image (*.comp)"));
	if(fileName != ""){
		decom->setFile(fileName.toStdString());
		if (decom->Open() == 0){
			QMessageBox::warning ( NULL, "Fout bij laden van bestand", "\nBestand niet gevonden... \n");
		}
		else{
			
			decom->Read();
			decom->toMatrix();
			decom->antiQuantisation();
			decom->antiDct();
			com->setHeight(decom->getHeight());
			com->setWidth(decom->getWidth());
			updateHeight(decom->getHeight());
			updateWidth(decom->getWidth());
			com->renewMatrix();
			if ( (com->getWidth() % currentBlocksize !=0) || (com->getHeight() % currentBlocksize !=0) )
			{
				ui.spinBlocksize->setValue(1);
				changeBlocksize(1);
			}
			com->setMatrix(decom->getMatrix());
			drawImage(com->getMatrix(), com->getWidth(), com->getHeight(), ui.screen);
		}
	}
}

/* Gecompileerde afbeelding opslaan als gecompileerd formaat *.comp */
void BeeldCompressieUI::save()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save the compressed image"), "/home/", tr("Compressed Image (*.comp)"));
	if(fileName != ""){
		com->toFile(fileName.toStdString());
		decom->setFile(fileName.toStdString());
	}
}

/* Gecompileerde file opslaan in *.raw formaat */
void BeeldCompressieUI::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save the compressed image as a raw image"), "/home/", tr("Raw Image (*.raw)"));
	if(fileName != ""){
		if (decom->toFile(fileName.toStdString()) == 0)
			QMessageBox::warning ( NULL, "Fout bij saven van bestand", "\nBestand niet gevonden... \n");
	}
}

/* Quantisatie start waarde wordt gewijzigd door gebruiker */
void BeeldCompressieUI::changeQStart(int start)
{
	com->setQStart(ui.spinQStart->value());
}

/* Quantisatie raise waarde wordt gewijzigd door gebruiker */
void BeeldCompressieUI::changeQRaise(int raise)
{
	com->setQRaise(ui.spinQRaise->value());
}

/* Height wijzigen in UI */
void BeeldCompressieUI::updateHeight(int height)
{
	ui.editHeight->setText(QString::number(height));
}

/* Width wijzigen in UI */
void BeeldCompressieUI::updateWidth(int width)
{
	ui.editWidth->setText(QString::number(width));
}

/* Bytes wijzigen in UI */
void BeeldCompressieUI::updateBytes(int bytes)
{
	ui.editBytes->setText(QString::number(bytes));
	ui.editKBytes->setText(QString::number(bytes/1024.0));
}

/* Blocksize voor te comprimeren wordt gewijzigd door gebruiker */
void BeeldCompressieUI::changeBlocksize(int blocksize)
{
	if (currentBlocksize < blocksize)
	{
		while ( (com->getWidth() % blocksize !=0) || (com->getHeight() % blocksize !=0) )
		{
			if (blocksize > com->getWidth() || blocksize > com->getHeight())
			{
				blocksize = currentBlocksize;
				break;
			}
			blocksize++;
		}
	}
	else if (currentBlocksize > blocksize)
	{
		while ( ((com->getWidth() % blocksize !=0) || (com->getHeight()) % blocksize !=0) && (blocksize != 1) )
		{
			blocksize--;
		}
	}
	currentBlocksize = blocksize;
	ui.spinBlocksize->setValue(blocksize);
	com->setBlocksize(ui.spinBlocksize->value());
}

/* De matrix van de een gecomprimeerde of niet gecomprimeerde file uittekenen */
/* hij wordt uitgetekend in de screen die je meegeeft (bv linke of rechtse screen */
void BeeldCompressieUI::drawImage(Matrix<int> ma, int width, int height, QGraphicsView* screen)
{
	QColor value;
	QImage im(width, height, QImage::Format_RGB32 );
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			int c = ma[i][j];
			if (c > 255)
				c = 255;
			if (c < 0)
				c = 0;
			value = QColor(c, c, c); 
			im.setPixel(j,i,value.rgb());
		}
	}
	
	QPixmap pix(width, height);
	pix = pix.fromImage(im);
	m_View = new QGraphicsScene();
	item = new QGraphicsPixmapItem(pix);
	m_View->addItem( item );
	screen->setScene(m_View);
}

/* Comprimeren van een afbeelding en uittekenen*/
void BeeldCompressieUI::on_pushComprimeren_clicked()
{
	backupMa = com->getMatrix();
	com->dct();
	com->quantisation();
	com->toArray();
	com->rle();
	decom->setWriter(com->getWriter());
	decom->Read();
	decom->toMatrix();
	decom->antiQuantisation();
	decom->antiDct();
	com->setMatrix(backupMa);

	Matrix<int> ma = decom->getMatrix();
	updateBytes(com->getLengthFile());
	drawImage(decom->getMatrix(), decom->getWidth(), decom->getHeight(), ui.screenCom);
}

/* About */
void BeeldCompressieUI::about()
{
	QMessageBox::about(this, "About", "Taak Technologie van Multimediasystemen en software, \ngemaakt door:\nKenneth Devloo (0623746)\nNick Michiels (0623764)\nGroep 2\n2008-2009");
}