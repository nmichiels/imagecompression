#ifndef BEELDCOMPRESSIEUI_H
#define BEELDCOMPRESSIEUI_H

#include <QtGui/QMainWindow>
#include "ui_beeldcompressieui.h"
#include <QPixmap.h>
#include <QGraphicsView.h>
#include <QImage.h>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "Compression.h"
#include "Decompression.h"
#include "Matrix.h"

#include <iostream>
using namespace std;

class BeeldCompressieUI : public QMainWindow
{
	Q_OBJECT

	public:
		BeeldCompressieUI(QWidget *parent = 0, Qt::WFlags flags = 0);
		~BeeldCompressieUI();

		

		

	private:
		Ui::BeeldCompressieUIClass ui;
		Matrix<int> backupMa;

		QGraphicsScene *m_View;
		QGraphicsPixmapItem *item;

		Compression *com;
		Decompression *decom;

		QString rawFile;

		int currentBlocksize;

		void drawImage(Matrix<int> ma, int height, int width, QGraphicsView* screen);

		void updateHeight(int height);
		void updateWidth(int width);
		void updateBytes(int bytes);

	private slots:
		void on_pushComprimeren_clicked();
		void open(void);
		void openAs(void);
		void save(void);
		void saveAs(void);
		void changeQStart(int start);
		void changeQRaise(int raise);
		void changeBlocksize(int blocksize);
		void about();
};

#endif // BEELDCOMPRESSIEUI_H
