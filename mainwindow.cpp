#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <QString>
#include <fstream>
#include <QIcon>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setText(QString::number(mark));
    ui->label_5->setText(QString::number(s));
    add();

    //start count
    eat();

}
MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::arr[10][10]={0};
int MainWindow::carr[10][10]={0};
int MainWindow::sarr[10][10]={0};
int MainWindow::first=0;
int MainWindow::second=0;
int MainWindow::mark=0;
int MainWindow::f=0;
int MainWindow::s=25;

void MainWindow::add(){
    srand(time(0));
    int a=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            a = rand()%5+1;
            if(arr[i][j]==0)
               arr[i][j]=a;
        }
     }
    pic();
}

void MainWindow::move(){
    for(int i=0;i<10;i++){
         for(int j=0;j<10;j++){
             if(j != 0 && arr[j][i]==0 && arr[j-1][i]!=0){
                 for(int k = 0; k < j; k++)
                     arr[j-k][i] = arr[j-k-1][i];
                     arr[0][i] = 0;
             }
         }
     }
}


void MainWindow::eat(){

    //長炸彈
    for(int i=0;i<10;i++){
        for(int j=0;j<8;j++){

            int ii=16,jj=1;
            while(ii<21 && jj<6){
                //橫排的橫炸彈
                if((arr[i][j]==ii && arr[i][j+1]==jj && arr[i][j+2]==jj) || (arr[i][j+1]==ii && arr[i][j]==jj && arr[i][j+2]==jj) || (arr[i][j+2]==ii && arr[i][j+1]==jj && arr[i][j]==jj)){
                    for(int k=0;k<10;k++)
                        arr[i][k]=99;
                }

                //直排的直炸彈
                if((arr[j][i]==ii-5 && arr[j+1][i]==jj && arr[j+2][i]==jj) || (arr[j][i]==jj && arr[j+1][i]==ii-5 && arr[j+2][i]==jj) || (arr[j][i]==jj && arr[j+1][i]==jj && arr[j+2][i]==ii-5)){
                    for(int k=0;k<10;k++)
                        arr[k][i]=99;
                }

                //直排的橫炸彈
                if(arr[j][i]==ii && arr[j+1][i]==jj && arr[j+2][i]==jj){
                    for(int k=0;k<10;k++)
                        arr[j][k]=99;
                }
                if(arr[j][i]==jj && arr[j+1][i]==ii && arr[j+2][i]==jj){
                    for(int k=0;k<10;k++)
                        arr[j+1][k]=99;
                }

                if(arr[j][i]==jj && arr[j+1][i]==jj && arr[j+2][i]==ii){
                    for(int k=0;k<10;k++)
                        arr[j+2][k]=99;
                }

                //橫排的直炸彈
                if(arr[i][j]==ii-5 && arr[i][j+1]==jj && arr[i][j+2]==jj){
                    for(int k=0;k<10;k++)
                        arr[k][j]=99;
                }
                if(arr[i][j+1]==ii-5 && arr[i][j]==jj && arr[i][j+2]==jj){
                    for(int k=0;k<10;k++)
                        arr[k][j+1]=99;
                }
                if(arr[i][j+2]==ii-5 && arr[i][j+1]==jj && arr[i][j]==jj){
                    for(int k=0;k<10;k++)
                        arr[k][j+2]=99;
                }
                ii++;
                jj++;
            }
            ii=16;
            jj=1;
        }
    }


    //如果是方形炸彈
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            int iii=6,jjj=1;
            while(iii<11 && jjj<6){

                if(arr[i][j]==iii && arr[i][j+1]==jjj && arr[i][j+2]==jjj){
                    arr[i-1][j-1]=99;
                    arr[i-1][j]=99;
                    arr[i-1][j+1]=99;
                    arr[i][j-1]=99;
                    arr[i][j]=99;
                    arr[i][j+1]=99;
                    arr[i+1][j-1]=99;
                    arr[i+1][j]=99;
                    arr[i+1][j+1]=99;
                }
                if(arr[i][j+1]==iii && arr[i][j]==jjj && arr[i][j+2]==jjj){
                    arr[i-1][j]=99;
                    arr[i-1][j+1]=99;
                    arr[i-1][j+2]=99;
                    arr[i][j]=99;
                    arr[i][j+1]=99;
                    arr[i][j+2]=99;
                    arr[i+1][j]=99;
                    arr[i+1][j+1]=99;
                    arr[i+1][j+2]=99;
                }
                if(arr[i][j+2]==iii && arr[i][j+1]==jjj && arr[i][j]==jjj){
                    arr[i-1][j+1]=99;
                    arr[i-1][j+2]=99;
                    arr[i-1][j+3]=99;
                    arr[i][j+1]=99;
                    arr[i][j+2]=99;
                    arr[i][j+3]=99;
                    arr[i+1][j+1]=99;
                    arr[i+1][j+2]=99;
                    arr[i+1][j+3]=99;
                }
                if(arr[j][i]==iii && arr[j+1][i]==jjj && arr[j+2][i]==jjj){
                    arr[j-1][i-1]=99;
                    arr[j-1][i]=99;
                    arr[j-1][i+1]=99;
                    arr[j][i-1]=99;
                    arr[j][i]=99;
                    arr[j][i+1]=99;
                    arr[j+1][i-1]=99;
                    arr[j+1][i]=99;
                    arr[j+1][i+1]=99;
                }
                if(arr[j+1][i]==iii && arr[j][i]==jjj && arr[j+2][i]==jjj){
                    arr[j][i-1]=99;
                    arr[j][i]=99;
                    arr[j][i+1]=99;
                    arr[j+1][i-1]=99;
                    arr[j+1][i]=99;
                    arr[j+1][i+1]=99;
                    arr[j+2][i-1]=99;
                    arr[j+2][i]=99;
                    arr[j+2][i+1]=99;
                }
                if(arr[j+2][i]==iii && arr[j][i]==jjj && arr[j+1][i]==jjj){
                    arr[j+1][i-1]=99;
                    arr[j+1][i]=99;
                    arr[j+1][i+1]=99;
                    arr[j+2][i-1]=99;
                    arr[j+2][i]=99;
                    arr[j+2][i+1]=99;
                    arr[j+3][i-1]=99;
                    arr[j+3][i]=99;
                    arr[j+3][i+1]=99;
                }
                iii++;
                jjj++;
            }
            iii=6;
            jjj=1;
        }
    }

    //橫排直排都可以吃
    for(int i=0;i<10;i++){
        for(int j=0;j<8;j++){
            if(arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2]){
                for(int z=0;z<10;z++){
                    for(int x=0;x<8;x++){
                        if(arr[x][z]==arr[x+1][z] && arr[x+1][z]==arr[x+2][z]){
                                //方形炸彈
                                if(arr[i][j]==1)
                                    arr[i][j]=6;
                                if(arr[i][j]==2)
                                    arr[i][j]=7;
                                if(arr[i][j]==3)
                                    arr[i][j]=8;
                                if(arr[i][j]==4)
                                    arr[i][j]=9;
                                if(arr[i][j]==5)
                                    arr[i][j]=10;

                                arr[i][j+1]=99;
                                arr[i][j+2]=99;
                                arr[x+1][z]=99;
                                arr[x+2][z]=99;
                        }
                    }
                }
            }

        }
    }

    //5個吃掉
    for(int i=0;i<10;i++){
        for(int j=0;j<6;j++){
            //橫排
            if(arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2] && arr[i][j+2]==arr[i][j+3] && arr[i][j+3]==arr[i][j+4]){
                arr[i][j]=99;
                arr[i][j+1]=99;
                arr[i][j+2]=21;
                arr[i][j+3]=99;
                arr[i][j+4]=99;
            }
            //直排
            if(arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i] && arr[j+2][i]==arr[j+3][i] && arr[j+3][i]==arr[j+4][i]){
                arr[j][i]=99;
                arr[j+1][i]=99;
                arr[j+2][i]=21;
                arr[j+3][i]=99;
                arr[j+4][i]=99;
            }
        }
    }

    //4個吃掉
    for(int i=0;i<10;i++){
        for(int j=0;j<7;j++){
            //橫排
            if(arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2] && arr[i][j+2]==arr[i][j+3]){
                arr[i][j]=99;
                if(arr[i][j+1]==1)
                    arr[i][j+1]=16;
                if(arr[i][j+1]==2)
                    arr[i][j+1]=17;
                if(arr[i][j+1]==3)
                    arr[i][j+1]=18;
                if(arr[i][j+1]==4)
                    arr[i][j+1]=19;
                if(arr[i][j+1]==5)
                    arr[i][j+1]=20;
                arr[i][j+2]=99;
                arr[i][j+3]=99;
            }
            //直排
            if(arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i] && arr[j+2][i]==arr[j+3][i]){
                arr[j][i]=99;
                if(arr[j+1][i]==1)
                    arr[j+1][i]=11;
                if(arr[j+1][i]==2)
                    arr[j+1][i]=12;
                if(arr[j+1][i]==3)
                    arr[j+1][i]=13;
                if(arr[j+1][i]==4)
                    arr[j+1][i]=14;
                if(arr[j+1][i]==5)
                    arr[j+1][i]=15;
                arr[j+2][i]=99;
                arr[j+3][i]=99;
            }
        }
    }

    //3個吃掉
    for(int i=0;i<10;i++){
        for(int j=0;j<8;j++){
            //橫排
            if(arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2]){
                arr[i][j]=99;
                arr[i][j+1]=99;
                arr[i][j+2]=99;
            }
            //直排
            if(arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i]){
                arr[j][i]=99;
                arr[j+1][i]=99;
                arr[j+2][i]=99;
            }
        }
    }
    //分數
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(arr[i][j]==99){
                arr[i][j]=0;
                mark=mark+20;

                ui->label_3->setText(QString::number(mark));
                //星星
                if(mark>=5000)
                    ui->label_7->setPixmap(QPixmap(":/pics/pic22.png"));
                if(mark>=10000)
                    ui->label_8->setPixmap(QPixmap(":/pics/pic22.png"));
                if(mark>=15000)
                    ui->label_9->setPixmap(QPixmap(":/pics/pic22.png"));
            }
        }
    }
    move();
    add();

//eat again
    for(int i=0;i<10;i++){
        for(int j=0;j<8;j++){
            if( (arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2]) || (arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i]) ){
                eat();
            }
            if(i==9 && j==7){
                break;
            }
        }
    }
//沒有東西的
    int check=0;
    if(carr[0][0]!=0){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(carr[i][j]==arr[i][j])
                    check++;
            }
        }
    }
    if(check==100){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                arr[i][j]=sarr[i][j];
                if(arr[i][j]==78)
                    arr[i][j]=first;
                if(arr[i][j]==87)
                    arr[i][j]=second;
            }
        }
        s=s+1;
        ui->label_5->setText(QString::number(s));
        if(s==0 && mark<5000){
             ui->label_10->setPixmap(QPixmap(":/pics/pic23.png"));
            ui->label_10->show();
        }
        if(s==0 && mark>5000 && mark<10000){
             ui->label_10->setPixmap(QPixmap(":/pics/pic24.png"));
            ui->label_10->show();
        }
        if(s==0 && mark>10000 && mark<15000){
             ui->label_10->setPixmap(QPixmap(":/pics/pic25.png"));
             ui->label_10->show();
        }
        if(s==0 && mark>15000){
             ui->label_10->setPixmap(QPixmap(":/pics/pic26.png"));
             ui->label_10->show();
        }

    }
}


void MainWindow::swap(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            sarr[i][j]=arr[i][j];
        }
    }

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(first==21){
                if(arr[i][j]==second||arr[i][j]==78||arr[i][j]==87)
                    arr[i][j]=99;
            }
            if(second==21){
                if(arr[i][j]==first||arr[i][j]==78||arr[i][j]==87)
                    arr[i][j]=99;
            }
        }
    }

    //start swap
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(arr[i][j]==78)
                arr[i][j]=second;
            if(arr[i][j]==87)
                arr[i][j]=first;
        }
    }

    s=s-1;
    ui->label_5->setText(QString::number(s));

    pic();
    //record array after swap
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            carr[i][j]=arr[i][j];
        }
    }
    eat();
}

void MainWindow::pic(){
    QIcon pics[26]={QIcon(":/pics/pic1.png"),
                   QIcon(":/pics/pic2.png"),
                   QIcon(":/pics/pic3.png"),
                   QIcon(":/pics/pic4.png"),
                   QIcon(":/pics/pic5.png"),
                   QIcon(":/pics/pic6.png"),
                   QIcon(":/pics/pic7.png"),
                   QIcon(":/pics/pic8.png"),
                   QIcon(":/pics/pic9.png"),
                   QIcon(":/pics/pic10.png"),
                   QIcon(":/pics/pic11.png"),
                   QIcon(":/pics/pic12.png"),
                   QIcon(":/pics/pic13.png"),
                   QIcon(":/pics/pic14.png"),
                   QIcon(":/pics/pic15.png"),
                   QIcon(":/pics/pic16.png"),
                   QIcon(":/pics/pic17.png"),
                   QIcon(":/pics/pic18.png"),
                   QIcon(":/pics/pic19.png"),
                   QIcon(":/pics/pic20.png"),
                   QIcon(":/pics/pic21.png"),
                   QIcon(":/pics/pic22.png"),
                   QIcon(":/pics/pic23.png"),
                   QIcon(":/pics/pic24.png"),
                   QIcon(":/pics/pic25.png"),
                   QIcon(":/pics/pic26.png"), };


    for(int k=0;k<22;k++){
       if(arr[0][0]==k+1)
            ui->pushButton->setIcon(pics[k]);
       if(arr[0][1]==k+1)
            ui->pushButton_2->setIcon(pics[k]);
       if(arr[0][2]==k+1)
            ui->pushButton_3->setIcon(pics[k]);
       if(arr[0][3]==k+1)
            ui->pushButton_4->setIcon(pics[k]);
       if(arr[0][4]==k+1)
            ui->pushButton_5->setIcon(pics[k]);
       if(arr[0][5]==k+1)
            ui->pushButton_6->setIcon(pics[k]);
       if(arr[0][6]==k+1)
            ui->pushButton_7->setIcon(pics[k]);
       if(arr[0][7]==k+1)
            ui->pushButton_8->setIcon(pics[k]);
       if(arr[0][8]==k+1)
            ui->pushButton_9->setIcon(pics[k]);
       if(arr[0][9]==k+1)
            ui->pushButton_10->setIcon(pics[k]);
       if(arr[1][0]==k+1)
            ui->pushButton_11->setIcon(pics[k]);
       if(arr[1][1]==k+1)
            ui->pushButton_12->setIcon(pics[k]);
       if(arr[1][2]==k+1)
            ui->pushButton_13->setIcon(pics[k]);
       if(arr[1][3]==k+1)
            ui->pushButton_14->setIcon(pics[k]);
       if(arr[1][4]==k+1)
            ui->pushButton_15->setIcon(pics[k]);
       if(arr[1][5]==k+1)
            ui->pushButton_16->setIcon(pics[k]);
       if(arr[1][6]==k+1)
            ui->pushButton_17->setIcon(pics[k]);
       if(arr[1][7]==k+1)
            ui->pushButton_18->setIcon(pics[k]);
       if(arr[1][8]==k+1)
            ui->pushButton_19->setIcon(pics[k]);
       if(arr[1][9]==k+1)
            ui->pushButton_20->setIcon(pics[k]);
       if(arr[2][0]==k+1)
            ui->pushButton_21->setIcon(pics[k]);
       if(arr[2][1]==k+1)
            ui->pushButton_22->setIcon(pics[k]);
       if(arr[2][2]==k+1)
            ui->pushButton_23->setIcon(pics[k]);
       if(arr[2][3]==k+1)
            ui->pushButton_24->setIcon(pics[k]);
       if(arr[2][4]==k+1)
            ui->pushButton_25->setIcon(pics[k]);
       if(arr[2][5]==k+1)
            ui->pushButton_26->setIcon(pics[k]);
       if(arr[2][6]==k+1)
            ui->pushButton_27->setIcon(pics[k]);
       if(arr[2][7]==k+1)
            ui->pushButton_28->setIcon(pics[k]);
       if(arr[2][8]==k+1)
            ui->pushButton_29->setIcon(pics[k]);
       if(arr[2][9]==k+1)
            ui->pushButton_30->setIcon(pics[k]);
       if(arr[3][0]==k+1)
            ui->pushButton_31->setIcon(pics[k]);
       if(arr[3][1]==k+1)
            ui->pushButton_32->setIcon(pics[k]);
       if(arr[3][2]==k+1)
            ui->pushButton_33->setIcon(pics[k]);
       if(arr[3][3]==k+1)
            ui->pushButton_34->setIcon(pics[k]);
       if(arr[3][4]==k+1)
            ui->pushButton_35->setIcon(pics[k]);
       if(arr[3][5]==k+1)
            ui->pushButton_36->setIcon(pics[k]);
       if(arr[3][6]==k+1)
            ui->pushButton_37->setIcon(pics[k]);
       if(arr[3][7]==k+1)
            ui->pushButton_38->setIcon(pics[k]);
       if(arr[3][8]==k+1)
            ui->pushButton_39->setIcon(pics[k]);
       if(arr[3][9]==k+1)
            ui->pushButton_40->setIcon(pics[k]);
       if(arr[4][0]==k+1)
            ui->pushButton_41->setIcon(pics[k]);
       if(arr[4][1]==k+1)
            ui->pushButton_42->setIcon(pics[k]);
       if(arr[4][2]==k+1)
            ui->pushButton_43->setIcon(pics[k]);
       if(arr[4][3]==k+1)
            ui->pushButton_44->setIcon(pics[k]);
       if(arr[4][4]==k+1)
            ui->pushButton_45->setIcon(pics[k]);
       if(arr[4][5]==k+1)
            ui->pushButton_46->setIcon(pics[k]);
       if(arr[4][6]==k+1)
            ui->pushButton_47->setIcon(pics[k]);
       if(arr[4][7]==k+1)
            ui->pushButton_48->setIcon(pics[k]);
       if(arr[4][8]==k+1)
            ui->pushButton_49->setIcon(pics[k]);
       if(arr[4][9]==k+1)
            ui->pushButton_50->setIcon(pics[k]);
       if(arr[5][0]==k+1)
            ui->pushButton_51->setIcon(pics[k]);
       if(arr[5][1]==k+1)
            ui->pushButton_52->setIcon(pics[k]);
       if(arr[5][2]==k+1)
            ui->pushButton_53->setIcon(pics[k]);
       if(arr[5][3]==k+1)
            ui->pushButton_54->setIcon(pics[k]);
       if(arr[5][4]==k+1)
            ui->pushButton_55->setIcon(pics[k]);
       if(arr[5][5]==k+1)
            ui->pushButton_56->setIcon(pics[k]);
       if(arr[5][6]==k+1)
            ui->pushButton_57->setIcon(pics[k]);
       if(arr[5][7]==k+1)
            ui->pushButton_58->setIcon(pics[k]);
       if(arr[5][8]==k+1)
            ui->pushButton_59->setIcon(pics[k]);
       if(arr[5][9]==k+1)
            ui->pushButton_60->setIcon(pics[k]);
       if(arr[6][0]==k+1)
            ui->pushButton_61->setIcon(pics[k]);
       if(arr[6][1]==k+1)
            ui->pushButton_62->setIcon(pics[k]);
       if(arr[6][2]==k+1)
            ui->pushButton_63->setIcon(pics[k]);
       if(arr[6][3]==k+1)
            ui->pushButton_64->setIcon(pics[k]);
       if(arr[6][4]==k+1)
            ui->pushButton_65->setIcon(pics[k]);
       if(arr[6][5]==k+1)
            ui->pushButton_66->setIcon(pics[k]);
       if(arr[6][6]==k+1)
            ui->pushButton_67->setIcon(pics[k]);
       if(arr[6][7]==k+1)
            ui->pushButton_68->setIcon(pics[k]);
       if(arr[6][8]==k+1)
            ui->pushButton_69->setIcon(pics[k]);
       if(arr[6][9]==k+1)
            ui->pushButton_70->setIcon(pics[k]);
       if(arr[7][0]==k+1)
            ui->pushButton_71->setIcon(pics[k]);
       if(arr[7][1]==k+1)
            ui->pushButton_72->setIcon(pics[k]);
       if(arr[7][2]==k+1)
            ui->pushButton_73->setIcon(pics[k]);
       if(arr[7][3]==k+1)
            ui->pushButton_74->setIcon(pics[k]);
       if(arr[7][4]==k+1)
            ui->pushButton_75->setIcon(pics[k]);
       if(arr[7][5]==k+1)
            ui->pushButton_76->setIcon(pics[k]);
       if(arr[7][6]==k+1)
            ui->pushButton_77->setIcon(pics[k]);
       if(arr[7][7]==k+1)
            ui->pushButton_78->setIcon(pics[k]);
       if(arr[7][8]==k+1)
            ui->pushButton_79->setIcon(pics[k]);
       if(arr[7][9]==k+1)
            ui->pushButton_80->setIcon(pics[k]);
       if(arr[8][0]==k+1)
            ui->pushButton_81->setIcon(pics[k]);
       if(arr[8][1]==k+1)
            ui->pushButton_82->setIcon(pics[k]);
       if(arr[8][2]==k+1)
            ui->pushButton_83->setIcon(pics[k]);
       if(arr[8][3]==k+1)
            ui->pushButton_84->setIcon(pics[k]);
       if(arr[8][4]==k+1)
            ui->pushButton_85->setIcon(pics[k]);
       if(arr[8][5]==k+1)
            ui->pushButton_86->setIcon(pics[k]);
       if(arr[8][6]==k+1)
            ui->pushButton_87->setIcon(pics[k]);
       if(arr[8][7]==k+1)
            ui->pushButton_88->setIcon(pics[k]);
       if(arr[8][8]==k+1)
            ui->pushButton_89->setIcon(pics[k]);
       if(arr[8][9]==k+1)
            ui->pushButton_90->setIcon(pics[k]);
       if(arr[9][0]==k+1)
            ui->pushButton_91->setIcon(pics[k]);
       if(arr[9][1]==k+1)
            ui->pushButton_92->setIcon(pics[k]);
       if(arr[9][2]==k+1)
            ui->pushButton_93->setIcon(pics[k]);
       if(arr[9][3]==k+1)
            ui->pushButton_94->setIcon(pics[k]);
       if(arr[9][4]==k+1)
            ui->pushButton_95->setIcon(pics[k]);
       if(arr[9][5]==k+1)
            ui->pushButton_96->setIcon(pics[k]);
       if(arr[9][6]==k+1)
            ui->pushButton_97->setIcon(pics[k]);
       if(arr[9][7]==k+1)
            ui->pushButton_98->setIcon(pics[k]);
       if(arr[9][8]==k+1)
            ui->pushButton_99->setIcon(pics[k]);
       if(arr[9][9]==k+1)
            ui->pushButton_100->setIcon(pics[k]);

    }
}
void MainWindow::on_pushButton_clicked(){
    if(first==0 && second==0){
        first = arr[0][0];
        arr[0][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][0];
        arr[0][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(first==0 && second==0){
        first = arr[0][1];
        arr[0][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][1];
        arr[0][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(first==0 && second==0){
        first = arr[0][2];
        arr[0][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][2];
        arr[0][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    if(first==0 && second==0){
        first = arr[0][3];
        arr[0][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][3];
        arr[0][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(first==0 && second==0){
        first = arr[0][4];
        arr[0][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][4];
        arr[0][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    if(first==0 && second==0){
        first = arr[0][5];
        arr[0][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][5];
        arr[0][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(first==0 && second==0){
        first = arr[0][6];
        arr[0][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][6];
        arr[0][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if(first==0 && second==0){
        first = arr[0][7];
        arr[0][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][7];
        arr[0][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(first==0 && second==0){
        first = arr[0][8];
        arr[0][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][8];
        arr[0][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    if(first==0 && second==0){
        first = arr[0][9];
        arr[0][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[0][9];
        arr[0][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    if(first==0 && second==0){
        first = arr[1][0];
        arr[1][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][0];
        arr[1][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    if(first==0 && second==0){
        first = arr[1][1];
        arr[1][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][1];
        arr[1][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if(first==0 && second==0){
        first = arr[1][2];
        arr[1][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][2];
        arr[1][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_14_clicked()
{
    if(first==0 && second==0){
        first = arr[1][3];
        arr[1][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][3];
        arr[1][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    if(first==0 && second==0){
        first = arr[1][4];
        arr[1][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][4];
        arr[1][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_16_clicked()
{
    if(first==0 && second==0){
        first = arr[1][5];
        arr[1][5]=87;
    }
    else if(first!=0 && second==0){
        second = arr[1][5];
        arr[1][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    if(first==0 && second==0){
        first = arr[1][6];
        arr[1][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][6];
        arr[1][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    if(first==0 && second==0){
        first = arr[1][7];
        arr[1][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][7];
        arr[1][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    if(first==0 && second==0){
        first = arr[1][8];
        arr[1][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][8];
        arr[1][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    if(first==0 && second==0){
        first = arr[1][9];
        arr[1][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[1][9];
        arr[1][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_21_clicked()
{
    if(first==0 && second==0){
        first = arr[2][0];
        arr[2][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][0];
        arr[2][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    if(first==0 && second==0){
        first = arr[2][1];
        arr[2][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][1];
        arr[2][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    if(first==0 && second==0){
        first = arr[2][2];
        arr[2][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][2];
        arr[2][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_24_clicked()
{
    if(first==0 && second==0){
        first = arr[2][3];
        arr[2][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][3];
        arr[2][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    if(first==0 && second==0){
        first = arr[2][4];
        arr[2][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][4];
        arr[2][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_26_clicked()
{
    if(first==0 && second==0){
        first = arr[2][5];
        arr[2][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][5];
        arr[2][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    if(first==0 && second==0){
        first = arr[2][6];
        arr[2][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][6];
        arr[2][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_28_clicked()
{
    if(first==0 && second==0){
        first = arr[2][7];
        arr[2][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][7];
        arr[2][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    if(first==0 && second==0){
        first = arr[2][8];
        arr[2][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][8];
        arr[2][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_30_clicked()
{
    if(first==0 && second==0){
        first = arr[2][9];
        arr[2][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[2][9];
        arr[2][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_31_clicked()
{
    if(first==0 && second==0){
        first = arr[3][0];
        arr[3][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][0];
        arr[3][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    if(first==0 && second==0){
        first = arr[3][1];
        arr[3][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][1];
        arr[3][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_33_clicked()
{
    if(first==0 && second==0){
        first = arr[3][2];
        arr[3][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][2];
        arr[3][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_34_clicked()
{
    if(first==0 && second==0){
        first = arr[3][3];
        arr[3][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][3];
        arr[3][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_35_clicked()
{
    if(first==0 && second==0){
        first = arr[3][4];
        arr[3][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][4];
        arr[3][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_36_clicked()
{
    if(first==0 && second==0){
        first = arr[3][5];
        arr[3][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][5];
        arr[3][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_37_clicked()
{
    if(first==0 && second==0){
        first = arr[3][6];
        arr[3][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][6];
        arr[3][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_38_clicked()
{
    if(first==0 && second==0){
        first = arr[3][7];
        arr[3][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][7];
        arr[3][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_39_clicked()
{
    if(first==0 && second==0){
        first = arr[3][8];
        arr[3][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][8];
        arr[3][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_40_clicked()
{
    if(first==0 && second==0){
        first = arr[3][9];
        arr[3][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[3][9];
        arr[3][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_41_clicked()
{
    if(first==0 && second==0){
        first = arr[4][0];
        arr[4][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][0];
        arr[4][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_42_clicked()
{
    if(first==0 && second==0){
        first = arr[4][1];
        arr[4][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][1];
        arr[4][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_43_clicked()
{
    if(first==0 && second==0){
        first = arr[4][2];
        arr[4][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][2];
        arr[4][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_44_clicked()
{
    if(first==0 && second==0){
        first = arr[4][3];
        arr[4][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][3];
        arr[4][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_45_clicked()
{
    if(first==0 && second==0){
        first = arr[4][4];
        arr[4][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][4];
        arr[4][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_46_clicked()
{
    if(first==0 && second==0){
        first = arr[4][5];
        arr[4][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][5];
        arr[4][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_47_clicked()
{
    if(first==0 && second==0){
        first = arr[4][6];
        arr[4][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][6];
        arr[4][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_48_clicked()
{
    if(first==0 && second==0){
        first = arr[4][7];
        arr[4][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][7];
        arr[4][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_49_clicked()
{
    if(first==0 && second==0){
        first = arr[4][8];
        arr[4][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][8];
        arr[4][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_50_clicked()
{
    if(first==0 && second==0){
        first = arr[4][9];
        arr[4][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[4][9];
        arr[4][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_51_clicked()
{
    if(first==0 && second==0){
        first = arr[5][0];
        arr[5][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][0];
        arr[5][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_52_clicked()
{
    if(first==0 && second==0){
        first = arr[5][1];
        arr[5][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][1];
        arr[5][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_53_clicked()
{
    if(first==0 && second==0){
        first = arr[5][2];
        arr[5][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][2];
        arr[5][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_54_clicked()
{
    if(first==0 && second==0){
        first = arr[5][3];
        arr[5][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][3];
        arr[5][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_55_clicked()
{
    if(first==0 && second==0){
        first = arr[5][4];
        arr[5][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][4];
        arr[5][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_56_clicked()
{
    if(first==0 && second==0){
        first = arr[5][5];
        arr[5][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][5];
        arr[5][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_57_clicked()
{
    if(first==0 && second==0){
        first = arr[5][6];
        arr[5][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][6];
        arr[5][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_58_clicked()
{
    if(first==0 && second==0){
        first = arr[5][7];
        arr[5][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][7];
        arr[5][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_59_clicked()
{
    if(first==0 && second==0){
        first = arr[5][8];
        arr[5][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][8];
        arr[5][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_60_clicked()
{
    if(first==0 && second==0){
        first = arr[5][9];
        arr[5][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[5][9];
        arr[5][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_61_clicked()
{
    if(first==0 && second==0){
        first = arr[6][0];
        arr[6][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][0];
        arr[6][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_62_clicked()
{
    if(first==0 && second==0){
        first = arr[6][1];
        arr[6][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][1];
        arr[6][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_63_clicked()
{
    if(first==0 && second==0){
        first = arr[6][2];
        arr[6][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][2];
        arr[6][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_64_clicked()
{
    if(first==0 && second==0){
        first = arr[6][3];
        arr[6][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][3];
        arr[6][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_65_clicked()
{
    if(first==0 && second==0){
        first = arr[6][4];
        arr[6][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][4];
        arr[6][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_66_clicked()
{
    if(first==0 && second==0){
        first = arr[6][5];
        arr[6][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][5];
        arr[6][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_67_clicked()
{
    if(first==0 && second==0){
        first = arr[6][6];
        arr[6][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][6];
        arr[6][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_68_clicked()
{
    if(first==0 && second==0){
        first = arr[6][7];
        arr[6][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][7];
        arr[6][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_69_clicked()
{
    if(first==0 && second==0){
        first = arr[6][8];
        arr[6][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][8];
        arr[6][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_70_clicked()
{
    if(first==0 && second==0){
        first = arr[6][9];
        arr[6][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[6][9];
        arr[6][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_71_clicked()
{
    if(first==0 && second==0){
        first = arr[7][0];
        arr[7][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][0];
        arr[7][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_72_clicked()
{
    if(first==0 && second==0){
        first = arr[7][1];
        arr[7][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][1];
        arr[7][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_73_clicked()
{
    if(first==0 && second==0){
        first = arr[7][2];
        arr[7][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][2];
        arr[7][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_74_clicked()
{
    if(first==0 && second==0){
        first = arr[7][3];
        arr[7][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][3];
        arr[7][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_75_clicked()
{
    if(first==0 && second==0){
        first = arr[7][4];
        arr[7][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][4];
        arr[7][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_76_clicked()
{
    if(first==0 && second==0){
        first = arr[7][5];
        arr[7][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][5];
        arr[7][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_77_clicked()
{
    if(first==0 && second==0){
        first = arr[7][6];
        arr[7][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][6];
        arr[7][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_78_clicked()
{
    if(first==0 && second==0){
        first = arr[7][7];
        arr[7][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][7];
        arr[7][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_79_clicked()
{
    if(first==0 && second==0){
        first = arr[7][8];
        arr[7][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][8];
        arr[7][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_80_clicked()
{
    if(first==0 && second==0){
        first = arr[7][9];
        arr[7][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[7][9];
        arr[7][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_81_clicked()
{
    if(first==0 && second==0){
        first = arr[8][0];
        arr[8][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][0];
        arr[8][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_82_clicked()
{
    if(first==0 && second==0){
        first = arr[8][1];
        arr[8][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][1];
        arr[8][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_83_clicked()
{
    if(first==0 && second==0){
        first = arr[8][2];
        arr[8][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][2];
        arr[8][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_84_clicked()
{
    if(first==0 && second==0){
        first = arr[8][3];
        arr[8][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][3];
        arr[8][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_85_clicked()
{
    if(first==0 && second==0){
        first = arr[8][4];
        arr[8][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][4];
        arr[8][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_86_clicked()
{
    if(first==0 && second==0){
        first = arr[8][5];
        arr[8][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][5];
        arr[8][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_87_clicked()
{
    if(first==0 && second==0){
        first = arr[8][6];
        arr[8][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][6];
        arr[8][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_88_clicked()
{
    if(first==0 && second==0){
        first = arr[8][7];
        arr[8][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][7];
        arr[8][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_89_clicked()
{
    if(first==0 && second==0){
        first = arr[8][8];
        arr[8][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][8];
        arr[8][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_90_clicked()
{
    if(first==0 && second==0){
        first = arr[8][9];
        arr[8][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[8][9];
        arr[8][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_91_clicked()
{
    if(first==0 && second==0){
        first = arr[9][0];
        arr[9][0]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][0];
        arr[9][0]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_92_clicked()
{
    if(first==0 && second==0){
        first = arr[9][1];
        arr[9][1]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][1];
        arr[9][1]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_93_clicked()
{
    if(first==0 && second==0){
        first = arr[9][2];
        arr[9][2]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][2];
        arr[9][2]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_94_clicked()
{
    if(first==0 && second==0){
        first = arr[9][3];
        arr[9][3]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][3];
        arr[9][3]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_95_clicked()
{
    if(first==0 && second==0){
        first = arr[9][4];
        arr[9][4]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][4];
        arr[9][4]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }

}

void MainWindow::on_pushButton_96_clicked()
{
    if(first==0 && second==0){
        first = arr[9][5];
        arr[9][5]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][5];
        arr[9][5]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_97_clicked()
{
    if(first==0 && second==0){
        first = arr[9][6];
        arr[9][6]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][6];
        arr[9][6]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_98_clicked()
{
    if(first==0 && second==0){
        first = arr[9][7];
        arr[9][7]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][7];
        arr[9][7]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_99_clicked()
{
    if(first==0 && second==0){
        first = arr[9][8];
        arr[9][8]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][8];
        arr[9][8]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}

void MainWindow::on_pushButton_100_clicked()
{
    if(first==0 && second==0){
        first = arr[9][8];
        arr[9][9]=78;
    }
    else if(first!=0 && second==0){
        second = arr[9][9];
        arr[9][9]=87;
    }
    if(first!=0 && second!=0){
        swap();
        first=0;
        second=0;
        eat();
    }
}
