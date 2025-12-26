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

#include "Headers/FriendsList.h"
#include <QStringList>
#include <QString>

    // #include <QDebug>

FriendsListObject::FriendsListObject(QObject *parent) : QObject(parent)
{

}

void FriendsListObject::set_data(QString plain_data){

    groups.clear();

    data = plain_data;
    QStringList plain_groups = data.split("|");

    plain_groups.removeFirst();
    nr_of_groups = plain_groups.count();

    QStringList buffer;

    for (int i=0; i < nr_of_groups; i++){

        buffer.append(plain_groups.at(i).split("/").at(0));
    }

    for (int i=0; i < nr_of_groups; i++){

        GroupObject *buffer_group = new GroupObject();
        buffer_group->set_group_name(buffer.at(i));
        groups.append(buffer_group);

        }

    for (int i=0; i < nr_of_groups; i++){
        groups.at(i)->set_plain_data(plain_groups.at(i));

        //qInfo() << "Group " + groups.at(i)->get_group_name() + " - Group Data: " + groups.at(i)->plain_group_data;
    }

    int position = 0;

    for (int i =0; i < groups.count(); i++){

        if ( i == 0 ){ groups.at(i)->group_list_position_index = position; }
        else {
            position = position + 1 + groups.at(i - 1)->group_peers_count();
            groups.at(i)->group_list_position_index = position;
        }
        //qInfo() << groups.at(i)->peers.count();


        for (int a = 0; a< groups.at(i)->peers.count(); a++){
            groups.at(i)->peers.at(a)->peer_list_position_index = position + a + 1;
            //qInfo() << groups.at(i)->peers.at(a)->peer_list_position_index;
        }

    }


}


GroupObject* FriendsListObject::group_at(int index){

    return groups.at(index);
}


GroupObject* FriendsListObject::newGroup(){

    groups.append(new GroupObject());
    groups.last()->set_group_name("New Group");

    //qInfo() << groups.at(groups.count() - 2)->group_name;
    groups.last()->group_list_position_index = groups.at(groups.count() - 2)->peers.last()->peer_list_position_index + 1;

    return groups.last();
}

void FriendsListObject::clear(){
    groups.clear();
}


IM_WindowObject* FriendsListObject::get_im_at(int index){

    IM_WindowObject *return_im = new IM_WindowObject();

    //qInfo() << groups.count();

    return return_im;

}
