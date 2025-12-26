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

#include "Headers/Peer.h"

PeerObject::PeerObject(QObject *parent) : QObject(parent)
{

    item_font.setBold(false);
    item_font.setItalic(false);
    item_font.setCapitalization(QFont::Capitalize);
    item_font.setPointSize(10);


}

void PeerObject::set_plain_data(QString plain_peer_data){

    plain_data = plain_peer_data;

    peer_data = plain_data.split("/");
    name = peer_data.at(0);
    email = peer_data.at(4);
    availability = peer_data.at(1);
    availability_int = peer_data.at(1).toInt();
    status_message = peer_data.at(2);

    if (availability == "0"){
        availability = "available";
    } else if (availability == "1"){
        availability = "busy";
    } else if (availability == "2"){
        availability = "offline";
    }


    im_window->setWindowTitle(name);
    im_window->list_index = peer_list_position_index;


    //qInfo() << "Name:'" + name + "'  " + "Availability:'" + availability + "'  " + "Status Message:'" + status_message + "'  " + " Email:'" + email + "' ;";


}

QStandardItem* PeerObject::get_item_model_item(){

    if (status_message == ""){separator = "";}

    if (availability_int == 0){
        list_icon=QIcon("/usr/local/share/QsMessenger/Resources/icons/indent_smiley.png");
    } else if (availability_int == 1) {
        list_icon=QIcon("/usr/local/share/QsMessenger/Resources/icons/indent_smiley_busy.png");
    } else if (availability_int == 2) {
        list_icon=QIcon("/usr/local/share/QsMessenger/Resources/icons/indent_smiley_invisible.png");
        item_font.setItalic(true);
        status_message = "";
    }


    item_model = new QStandardItem(spacer + name + separator + status_message);
    item_model->setIcon(list_icon);
    item_model->setFont(item_font);
    if (email.size() > 0){
    item_model->setToolTip(email);
    }


    return item_model;

}

IM_WindowObject* PeerObject::get_im_window(){

    //qInfo() << peer_list_position_index;

    return im_window;

}
