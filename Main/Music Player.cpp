#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<stack>
#include<SFML/Audio.hpp>
using namespace std;
struct prev_songs{
	string name;
	string artists;
	string album;
	string dur;
					
}ps;
class song{
	public:
		string name;
		string artists;
		string album;
		string dur;
		song* prev;
		song* next;
		song(string na, string arts, string alfi,string duration){
			name=na;
			artists=arts;
			album=alfi;
			dur=duration;
			prev=NULL;
			next=NULL;
		}
};
song *start=NULL, *curr, *node;
void playlist(string name, string arts, string alfi,string dura){
	node=new song(name,arts,alfi,dura);
	if(start==NULL){
		start=node;
		curr=node;
	}
	else{
		curr->next=node;
		node->prev=curr;
		curr=node;
	}
}
class MusicPlayer{
	string playlist_path;
	string playlist_name;
	string song_path;
	string song_name;
	string artists;
	string album;
	string dur;
	public:
		MusicPlayer(){
			playlist_path="D:/Projects/Music Player/Playlists/";
			song_path="D:/Projects/Music Player/Songs/";
		}
		void main_menu();
		void create_new_playlist();
		void open_playlist();
		void delete_playlist();
		void add();
		void save();
		void display_playlist();
		void edit();
		void play_complete_playlist();
		void play_specific_song();
		void delete_song();
		void reverse_playlist();
		void change_seq();
		void edit_song_name();
		void edit_artists();
		void edit_album_name();
		void edit_duration();
		void show_prev_played_songs();
		int convertToSeconds(string& duration);
		int sumDur(song* temp);
		string totalDur(int totalSeconds);
		
}mp;
int flag=0;
int MusicPlayer::convertToSeconds(string& duration) {
    int minutes = 0;
    int seconds = 0;

    char colon; 

    stringstream ss(duration);
    ss >> minutes >> colon >> seconds;

    if (ss.fail() || colon != ':' || minutes < 0 || seconds < 0 || seconds >= 60) {
        std::cerr << "Invalid duration format" << std::endl;
        return -1;
    }

    return (minutes * 60) + seconds;
}
int MusicPlayer::sumDur(song* temp){
	int sum=0;
	while(temp!=NULL){
		sum+=convertToSeconds(temp->dur);
		temp=temp->next;
	}
	return sum;
}
string MusicPlayer::totalDur(int totalSeconds) {
    if (totalSeconds < 0) {
        return "Invalid time";
    }

	int hours = totalSeconds/3600;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    stringstream ss;
    ss <<setw(2) << setfill('0') << hours << ":"<< setw(2) << setfill('0') << minutes << ":"
       << std::setw(2) << std::setfill('0') << seconds;

    return ss.str();
}

void MusicPlayer::main_menu(){
	int choice=0;
	while(choice!=4){
		cout<<"\n\t\t\t\t********************************";
		cout<<"\n\t\t\t\t* Welcome to Amiz Music Player *";
		cout<<"\n\t\t\t\t********************************";
		cout<<"\n\t\t\t\t********** Main Menu ***********";
		cout<<"\n\t\t\t\t********************************";
		cout<<"\n\t\t\t\t1.Create new playlist";
		cout<<"\n\t\t\t\t2.Open a playlist";
		cout<<"\n\t\t\t\t3.Delete playlist";
		cout<<"\n\t\t\t\t4.Exit";
		cout<<"\n\t\t\t\tChoice: ";
		cin>>choice;
		switch(choice){
			case 1: create_new_playlist();break;
			case 2: open_playlist();break;
			case 3: delete_playlist();break;
			case 4: cout<<"\n\t\t\t\tTerminated Successfully\n\n"; return;
			default:{
			cout<<"\n\t\t\t\tWrong choice"; 
			cout<<"\n\t\t\t\tPress enter to continue"; 
			cin.get();
			cin.get();
			}
		}
	}
}
void MusicPlayer::create_new_playlist(){
	cout << "\n\t\t\t\tName of the playlist: ";
    cin.ignore(); 
    getline(cin, playlist_name);
    int choice;
    while(choice!=2){
    	cout << "\n\t\t\t\t1.Add a song";
    	cout << "\n\t\t\t\t2.Save the playlist";
    	cout<<"\n\t\t\t\tChoice: ";
    	cin>>choice;
    	switch(choice){
    		case 1: add(); break;
    		case 2: save(); return;
    		default:{
			cout<<"\n\t\t\t\tWrong choice"; 
			cout<<"\n\t\t\t\tPress enter to continue"; 
			cin.get();
			cin.get();
			}
		}
	}
    cout << "\n\t\t\t\tPress enter to continue.";
    cin.get();
}
void MusicPlayer::add(){
	cin.ignore();
	cout << "\n\t\t\t\tName of the song: ";
	getline(cin,song_name);
	cout << "\n\t\t\t\tNames of artists: ";
	getline(cin,artists);
	cout << "\n\t\t\t\tAlbum: ";
	getline(cin,album);	
	cout << "\n\t\t\t\tDuration: ";
	getline(cin,dur);	
	playlist(song_name,artists,album,dur);
	if(flag==1){
		flag=0;
		return;
	}
	cout << "\n\t\t\t\tPress enter to continue.";
    cin.get();
}
void MusicPlayer::save(){
	if(start==NULL){
		cout<<"\n\t\t\t\tNo song added";
		cout<<"\n\t\t\t\tPlease add a song to save the playlist: "<<playlist_name;
		flag=1;
		add();
	}
	ofstream fout((playlist_path+playlist_name).c_str(), ios::binary);
	if(fout){
		song *temp=start;
		while(temp!=NULL){
			size_t l1 = temp->name.size();
        	fout.write(reinterpret_cast<const char*>(&l1), sizeof(l1));
        	fout.write(temp->name.c_str(), l1); 
        	
			size_t l2 = temp->artists.size();
        	fout.write(reinterpret_cast<const char*>(&l2), sizeof(l2));
        	fout.write(temp->artists.c_str(), l2); 
        	
			size_t l3 = temp->album.size();
        	fout.write(reinterpret_cast<const char*>(&l3), sizeof(l3));
        	fout.write(temp->album.c_str(), l3);
			curr=temp;
			
			size_t l4 = temp->dur.size();
        	fout.write(reinterpret_cast<const char*>(&l4), sizeof(l4));
        	fout.write(temp->dur.c_str(), l4); 
			temp=temp->next;
			delete curr;
		}
		cout << "\n\t\t\t\tPlaylist saved successfully.";
		start=NULL;
	}
    else {
        cout << "\n\t\t\t\tFailed to save playlist.";
    }
    fout.close();
}

void MusicPlayer::open_playlist(){
	cout << "\n\t\t\t\tName of the playlist: ";
    cin.ignore(); 
    getline(cin, playlist_name);
	ifstream fin((playlist_path+playlist_name).c_str(),ios::binary);
	if (!fin) {
        cerr <<"\n\t\t\t\tError opening the playlist: " << playlist_name;
        return;
    }
    while(fin){
    	size_t l1,l2,l3,l4;
        fin.read(reinterpret_cast<char*>(&l1), sizeof(l1));
        char* buff1 = new char[l1 + 1];
        fin.read(buff1, l1);
        buff1[l1] = '\0'; 
        
        fin.read(reinterpret_cast<char*>(&l2), sizeof(l2));
        char* buff2 = new char[l2 + 1];
        fin.read(buff2, l2);
        buff2[l2] = '\0'; 
        
        fin.read(reinterpret_cast<char*>(&l3), sizeof(l3));
        char* buff3 = new char[l3 + 1];
        fin.read(buff3, l3);
        buff3[l3] = '\0'; 
        
        fin.read(reinterpret_cast<char*>(&l4), sizeof(l4));
        char* buff4 = new char[l4 + 1];
        fin.read(buff4, l4);
        buff4[l4] = '\0'; 
        playlist(string(buff1),string(buff2),string(buff3),string(buff4));

        delete[] buff1;
        delete[] buff2;
        delete[] buff3;
        delete[] buff4;
		if(fin.eof()) break; 
	}
	fin.close();
	curr=curr->prev;
	curr->next=NULL;
	delete node;
	
	display_playlist();
	int choice=0;
	while(choice!=7){
		cout<<"\n\t\t\t\t1.Add a new song";
		cout<<"\n\t\t\t\t2.Edit the playlist";
		cout<<"\n\t\t\t\t3.Display the playlist";
		cout<<"\n\t\t\t\t4.Play complete playlist";
		cout<<"\n\t\t\t\t5.Play specific song";
		cout<<"\n\t\t\t\t6.Show previously played songs";
		cout<<"\n\t\t\t\t7.Save and Close the playlist";
		cout<<"\n\t\t\t\tChoice: ";
		cin>>choice;
		switch(choice){
			case 1: add();break;
			case 2: edit();break;
			case 3: cin.ignore();display_playlist(); break;
			case 4: play_complete_playlist();break;
			case 5: play_specific_song();break;
			case 6: show_prev_played_songs();break;
			case 7: save();return;
			default:{
			cout<<"\n\t\t\t\tWrong choice"; 
			cout<<"\n\t\t\t\tPress enter to continue"; 
			cin.get();
			cin.get();
			}
		}
	}		
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();

}
void MusicPlayer::delete_playlist(){
	cout << "\n\t\t\t\tName of the playlist: ";
    cin.ignore(); 
    getline(cin, playlist_name);
    if (remove((playlist_path+playlist_name).c_str()) == 0) {
        cout <<"\n\t\t\t\tPlaylist deleted successfully.";
    } else {
        cerr<<"\n\t\t\t\tError deleting playlist.";
    }
    cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::edit(){
	int choice =0;
	while(choice!=8){
		cout<<"\n\t\t\t\t1.Delete a song";
		cout<<"\n\t\t\t\t2.Edit song name";
		cout<<"\n\t\t\t\t3.Edit artists";
		cout<<"\n\t\t\t\t4.Edit album name";
		cout<<"\n\t\t\t\t5.Edit duration";
		cout<<"\n\t\t\t\t6.Reverse the playlist";
		cout<<"\n\t\t\t\t7.Change sequence of songs";
		cout<<"\n\t\t\t\t8.Go Back";
		cout<<"\n\t\t\t\tChoice: ";
		cin>>choice;
		switch(choice){
			case 1: delete_song(); break;
			case 2: edit_song_name();break;
			case 3: edit_artists();break;
			case 4: edit_album_name();break;
			case 5: edit_duration();break;
			case 6: reverse_playlist();break;
			case 7: change_seq(); break;
			case 8: return;
			default:{
			cout<<"\n\t\t\t\tWrong choice"; 
			cout<<"\n\t\t\t\tPress enter to continue"; 
			cin.get();
			cin.get();
			}
		}
	}

}
void MusicPlayer::delete_song(){
	int n;
	cout<<"\n\t\t\t\tSr.No. of song to delete: ";
	cin>>n;
	song *temp=start;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range."; 
	else{
		if(temp->prev==NULL) start=temp->next;
		else if(temp->next==NULL) temp->prev=NULL;
		else{
		temp->prev->next=temp->next;
		temp->next->prev=temp->prev;}
		cout<<"\n\t\t\t\tSong deleted: "<<temp->name;
		delete temp;
	}
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();	
	cin.get();
}
void MusicPlayer::edit_song_name(){
	int n;
	cout<<"\n\t\t\t\tSr.No. of song to edit its name: ";
	cin>>n;
	song *temp=start;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range."; 
	else{
		string newname;
		cout<<"\n\t\t\t\tNew name: ";
		cin.ignore();
		getline(cin,newname);
		temp->name=newname;
		cout<<"\n\t\t\t\tSong name editted successfully";
	}
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::edit_artists(){
	int n;
	cout<<"\n\t\t\t\tSr.No. of song to edit its artist names: ";
	cin>>n;
	song *temp=start;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range."; 
	else{
		string newartists;
		cout<<"\n\t\t\t\tNew artist names: ";
		cin.ignore();
		getline(cin,newartists);
		temp->artists=newartists;
		cout<<"\n\t\t\t\tArtists' names editted successfully";
	}
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::edit_album_name(){
	int n;
	cout<<"\n\t\t\t\tSr.No. of song to edit its album name: ";
	cin>>n;
	song *temp=start;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range."; 
	else{
		string newalbum;
		cout<<"\n\t\t\t\tNew album name: ";
		cin.ignore();
		getline(cin,newalbum);
		temp->album=newalbum;
		cout<<"\n\t\t\t\tAlbum name editted successfully";
	}
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::edit_duration(){
	int n;
	cout<<"\n\t\t\t\tSr.No. of song to edit its album name: ";
	cin>>n;
	song *temp=start;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range."; 
	else{
		string newdur;
		cout<<"\n\t\t\t\tNew duration: ";
		cin.ignore();
		getline(cin,newdur);
		temp->dur=newdur;
		cout<<"\n\t\t\t\tDuration editted successfully";
	}
	cin.ignore();
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::reverse_playlist(){
	song *temp=start;
	curr=start;
	song *pn=NULL;
	song *pp=NULL;
	while(temp!=NULL){
		pn=temp->next;
		temp->next=pp;
		temp->prev=pn;
		pp=temp;
		temp=pn;
	}
	start=pp;
	cout<<"\n\t\t\t\tPlaylist reversed successfully";
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::change_seq(){
	int curp,newp,cp,np;
	cout<<"\n\t\t\t\tEnter Sr.No. of song to shift: ";
	cin>>curp;
	song *temp=start;
	cp=curp;
	while(temp!=NULL){
		cp--;
		if(cp==0) break;
		temp=temp->next;
	}
	if(cp>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range.";
	else{
	cout<<"\n\t\t\t\tEnter new Sr.No. specifying new position: ";
	cin>>newp;
	song *ptr=start;
	np=newp;
	while(ptr!=NULL){
		np--;
		if(np==0) break;
		ptr=ptr->next;
	}
	if(np>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range.";
	else if(curp==newp) cout<<"\n\t\t\t\tWrong choice. Current position and new position can't be same'";
	
	else if(newp<curp){
		temp->prev->next=temp->next;
		temp->next->prev=temp->prev;
		if(ptr==start) {
		temp->prev=NULL;
		start=temp;
		}
		else {
		curr=ptr->prev;
		curr->next=temp;
		temp->prev=curr;
		}
		temp->next=ptr;
		ptr->prev=temp;
	}
	else{
		temp->next->prev=temp->prev;
		if(temp==start){
			start=temp->next;
		}
		else{
			temp->prev->next=temp->next;
		}
		curr=ptr->next;
		ptr->next=temp;
		temp->prev=ptr;
		temp->next=curr;
		if(curr!=NULL) curr->prev=temp;
		
	}
	cout<<"\n\t\t\t\tSequence changed successfully.";
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
 }
	
}
void MusicPlayer::display_playlist(){
	int sr_no = 1;
    const char separator = ' ';
    const int NoWidth = 9;       
    const int SongWidth = 17;     
    const int ArtistsWidth = 17;  
    const int AlbumWidth = 16;    
    const int DurationWidth = 12; 
    int sum=sumDur(start);
    
    cout << "\n\t\t\t   " << setw(14) << left << playlist_name << setw(8) << setfill(separator)<<totalDur(sum);
    cout << "\n\t\t\t   -----------------------";
    cout << "\n\n   +----------+------------------+-----------------+----------------+------------+";
    cout << "\n   | Sr No.   |    Song Name     |     Artists     |   Album Name   |  Duration  |";
    cout << "\n   +----------+------------------+-----------------+----------------+------------+";

    song* temp = start;
    while (temp!=NULL) {
        cout << "\n   |" << setw(0) <<sr_no<< setw(NoWidth) << setfill(separator) << "";
        cout << "|" << setw(SongWidth) << left << temp->name << setw(0) << setfill(separator) << " |";
        cout << setw(ArtistsWidth) << left << temp->artists << setw(0) << setfill(separator) << "|";
        cout << setw(AlbumWidth) << left << temp->album << setw(0) << setfill(separator) << "|";
        cout << setw(DurationWidth) << left << temp->dur << setw(0) << setfill(separator) << "|";
        sr_no++;
        temp = temp->next;
    }
    cout << "\n   +----------+------------------+-----------------+----------------+------------+";
    cout << "\n\n\n\t\t\tPress enter to continue.";
	cin.get();
}
stack<prev_songs>st;
void MusicPlayer::play_complete_playlist(){
	sf::Music music;
	song *temp=start;
    if (!music.openFromFile((song_path+temp->name+".wav"))) {
        cerr << "\n\t\t\t\tError loading " <<temp->name;
        flag=1;
    }

    char command;
    bool isPlaying = false;

    
    while (true) {
    	if(flag==1) break;
		cout << "\n\t\t\t\tCommands: p = play/pause, n = next, b = previous, q = quit";
		cout << "\n\t\t\t\tEnter command: ";
        cin>>command;

        switch (command) {
            case 'p': 
                if (isPlaying) {
                    music.pause();
                    cout << "\n\t\t\t\tPaused";
                } else {
                    music.play();
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
                    st.push(ps);
                }
                isPlaying = !isPlaying;
                break;

            case 'n': 
                music.stop();
                temp=temp->next;
                if (temp != NULL) {
                    if (!music.openFromFile(song_path+temp->name+".wav")) {
                        cerr << "\n\t\t\t\tError loading " << temp->name;
                        flag=1;
                        break;
                    }
                    music.play();
                    isPlaying = true;
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
                    st.push(ps);
                } else {
                    cout << "\n\t\t\t\tEnd of playlist reached";
                    isPlaying = false;
                }
                break;

            case 'b': 
                music.stop();
                if (temp->prev !=NULL ) {
                   temp=temp->prev;
                    if (!music.openFromFile(song_path+temp->name+".wav")) {
                        cerr << "\n\t\t\t\tError loading " << temp->name;
                        flag=1;
                        break;
                    }
                    music.play();
                    isPlaying = true;
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
                    st.push(ps);
                } else {
                    cout << "\n\t\t\t\tAlready at the first track";
                    isPlaying=false;
                }
                break;

            case 'q': 
                cout << "\n\t\t\t\tExiting...";
                music.stop();
                break;

            default:
                std::cout << "\n\t\t\t\tInvalid command";
                break;
        }
        if(command=='q'||temp==NULL||flag==1){
			flag=0;
			break;
		}
    }
    cin.ignore();
    cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}
void MusicPlayer::play_specific_song(){
	sf::Music music;
	int n;
	song *temp=start;
	cout<<"\n\t\t\t\tEnter Sr.No. of song to play: ";
	cin>>n;
	while(temp!=NULL){
		n--;
		if(n==0) break;
		temp=temp->next;
	}
	if(n>0) cout<<"\n\t\t\t\tWrong choice. Please enter a number within playlist's' range.";
	else{
		if (!music.openFromFile((song_path+temp->name+".wav"))) {
        cerr << "\n\t\t\t\tError loading " <<temp->name;
        flag=1;
    }

    char command;
    bool isPlaying = false;
    while (true) {
    	if(flag==1) break;
		cout << "\n\t\t\t\tCommands: p = play/pause, n = next, b = previous, q = quit";
		cout << "\n\t\t\t\tEnter command: ";
        cin>>command;

        switch (command) {
            case 'p': 
                if (isPlaying) {
                    music.pause();
                    cout << "\n\t\t\t\tPaused";
                } else {
                    music.play();
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
					st.push(ps);
                }
                isPlaying = !isPlaying;
                break;

            case 'n': 
                music.stop();
                temp=temp->next;
                if (temp != NULL) {
                    if (!music.openFromFile(song_path+temp->name+".wav")) {
                        cerr << "\n\t\t\t\tError loading " << temp->name;
                        flag=1;
                        break;
                    }
                    music.play();
                    isPlaying = true;
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
					st.push(ps);
                } else {
                    cout << "\n\t\t\t\tEnd of playlist reached";
                    isPlaying = false;
                }
                break;

            case 'b': 
                music.stop();
                if (temp->prev !=NULL ) {
                   temp=temp->prev;
                    if (!music.openFromFile(song_path+temp->name+".wav")) {
                        cerr << "\n\t\t\t\tError loading " << temp->name;
                        flag=1;
                        break;
                    }
                    music.play();
                    isPlaying = true;
                    cout << "\n\t\t\t\tNow Playing: " << temp->name;
                    ps.name=temp->name;
                    ps.artists=temp->artists;
                    ps.album=temp->album;
                    ps.dur=temp->dur;
                    st.push(ps);
                } else {
                    cout << "\n\t\t\t\tAlready at the first track";
                    isPlaying=false;
                }
                break;

            case 'q': 
                cout << "\n\t\t\t\tExiting...";
                music.stop();
                break;

            default:
                std::cout << "\n\t\t\t\tInvalid command";
                break;
        	}
        	if(command=='q'||flag==1||temp==NULL) {
        		flag=0;
        		break;
			}
    	}
	}
	cin.ignore();
	cout<<"\n\t\t\t\tPress enter to continue"; 
	cin.get();
}

void MusicPlayer::show_prev_played_songs(){
	stack<prev_songs>out=st;
	if(out.empty()){
	cout << "\n\n\n\t\t\tNo songs played previously.";
	cin.ignore();
	cout << "\n\n\n\t\t\tPress enter to continue.";
	cin.get();
	return;
	}
	int sr_no = 1;
    const char separator = ' ';
    const int NoWidth = 9;       
    const int SongWidth = 17;     
    const int ArtistsWidth = 17;  
    const int AlbumWidth = 16;    
    const int DurationWidth = 12; 

    cout << "\n\t\t\t   " << setw(14) << setfill(separator) << "Previously Played Songs" << setw(8) << setfill(separator);
    cout << "\n\t\t\t   -----------------------";
    cout << "\n\n   +----------+------------------+-----------------+----------------+------------+";
    cout << "\n   | Sr No.   |    Song Name     |     Artists     |   Album Name   |  Duration  |";
    cout << "\n   +----------+------------------+-----------------+----------------+------------+";
    
    while (!out.empty()) {
        cout << "\n   |" << setw(0) <<sr_no<< setw(NoWidth) << setfill(separator) << "";
        cout << "|" << setw(SongWidth) << left << out.top().name << setw(0) << setfill(separator) << " |";
        cout << setw(ArtistsWidth) << left << out.top().artists << setw(0) << setfill(separator) << "|";
        cout << setw(AlbumWidth) << left << out.top().album << setw(0) << setfill(separator) << "|";
        cout << setw(DurationWidth) << left << out.top().dur << setw(0) << setfill(separator) << "|";
        sr_no++;
        out.pop();
    }
    cout << "\n   +----------+------------------+-----------------+----------------+------------+";
    cin.ignore();
    cout << "\n\n\n\t\t\tPress enter to continue.";
	cin.get();
}
int main(){
	mp.main_menu();
}
