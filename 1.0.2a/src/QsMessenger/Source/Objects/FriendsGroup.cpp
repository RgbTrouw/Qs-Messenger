/*   QsMessenger Client v 1.0.2a Instant Messaging Application
     Copyright (C) 2026  Radu G. Balaban G.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "Headers/FriendsGroup.h"

    // #include <QDebug>


GroupObject::GroupObject(QObject *parent) : QObject(parent)
{

    item_font.setBold(false);
    item_font.setItalic(false);
    item_font.setCapitalization(QFont::Capitalize);
    item_font.setPointSize(10);

}

void GroupObject::set_group_name(QString name){
    group_name = name;
}

QString GroupObject::get_group_name(){

    return group_name;
}

void GroupObject::set_plain_data(QString plain_data){

    //qInfo() << "Group: " + group_name;

    if (plain_data.right(1) == ":"){
        plain_data = plain_data.left(plain_data.size() - 1);
    }

    QStringList buffer = plain_data.split(":");
    buffer.removeFirst();
    QString buffer_data;

    for (int i = 0; i < buffer.size(); i++){

        buffer_data.append(buffer.at(i));
            if (i != buffer.size() -1){
                buffer_data.append(":");
            }
    }

   plain_data = buffer_data;
   plain_group_data = plain_data;

   QStringList plain_group_data_sl;
   plain_group_data_sl = plain_group_data.split(":");


   for (int i = 0; i < plain_group_data_sl.count(); i++){
       PeerObject *peer_obj = new PeerObject();
       peer_obj->set_plain_data(plain_group_data_sl.at(i));
       peers.append(peer_obj);
       peers.last()->peer_list_position_index = group_list_position_index + i;
       //qInfo() << group_list_position_index;
       //qInfo() << peers.last()->peer_list_position_index;

   }


}

int GroupObject::group_peers_count(){
    return peers.count();
}

int GroupObject::group_peers_online_count(){
    int count = 0;

    for (int i=0; i<peers.count(); i++){
        if (peers.at(i)->availability_int == 0 ||peers.at(i)->availability_int == 1){
            count +=1;
        }
    }

    return count;
}



QStandardItem* GroupObject::get_item_model_item(){

    if (group_name != "New Group"){
    item_model = new QStandardItem(group_name + " (" + QString::number(group_peers_online_count()) + "/" + QString::number(group_peers_count()) + ")");
    item_model->setEditable(false);
    } else { item_model = new QStandardItem(group_name ); item_model->setEditable(true);}

    item_model->setFont(item_font);
    item_model->setForeground(QColor::fromRgb(52, 101, 164));

    return item_model;

}


PeerObject* GroupObject::get_user_at(int index){

    return peers.at(index);
}
