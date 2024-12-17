#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Helper {
public:
	static int StringLength(const char* str);
	static void StringCopy(char*& dest, char*& src);
	static void Display(char* str);
	static char* GetStringFromBuffer(char* str);
	static bool searchString(char* str, char* subStr);
	static bool MatchString(char* str1, char* str2);
	static char* strcat(char*, const char*);
};
char* Helper::strcat(char* str1, const char* str2) {
	char* str;
	int len = Helper::StringLength(str1) + Helper::StringLength(str2) + 1;
	str = new char[len];
	for (int i = 0; i < Helper::StringLength(str1); i++) {
		str[i] = str1[i];
	}
	int j = 0;
	for (int i = Helper::StringLength(str1); i < Helper::StringLength(str1) + Helper::StringLength(str2); i++) {
		str[i] = str2[j];
		j++;
	}
	str[len - 1] = '\0';
	return str;
}
bool Helper::searchString(char* str, char* subStr) {
	bool flag = false;
	int len = strlen(subStr);
	for (int y = 0; str[y] != '\0'; y++) {
		if (subStr[0] == str[y]) {
			flag = true;
		}
		if (flag) {
			for (int x = 0; x < len; x++) {
				if (subStr[x] != str[x + y]) {
					flag = false;
					break;
				}
			}
			if (flag) break;
		}
	}
	return flag;
}
bool Helper::MatchString(char* str1, char* str2) {
	bool flag = true;
	for (int i = 0; str2[i] != '\0'; i++) {
		if (str1[i] != str2[i]) {
			flag = false;
		}
	}
	return flag;
}
int Helper::StringLength(const char* str)
{
	int len = 0;
	for (int i = 0; str[i] != '\0'; i++)
		len++;
	return len;
}
void Helper::StringCopy(char*& dest, char*& src) {
	int lenght = StringLength(src);
	int i = 0;
	for (; i < lenght; i++)
		dest[i] = src[i];
	dest[i] = '\0';

}
void Helper::Display(char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		cout << str[i];
	}
}
char* Helper::GetStringFromBuffer(char* str)
{
	int length = StringLength(str);
	char* newStr = new char[length + 1];
	StringCopy(newStr, str);

	return newStr;
}
class Activity {
private:
	int Type;
	char* Value;
public:
	Activity();
	~Activity();
	void ReadFromFile(ifstream& fin);
	void Print();
};
Activity::Activity() {
	Type = 0;
	Value = 0;
}
void Activity::ReadFromFile(ifstream& fin) {
	char temp[50];
	fin >> Type;
	fin.getline(temp, 50);
	Value = Helper::GetStringFromBuffer(temp);
}
void Activity::Print() {

	if (Type == 1) {
		cout << " is feeling ";
		Helper::Display(Value);
	}
	else if (Type == 2) {
		cout << " is thinking about";
		Helper::Display(Value);
	}
	else if (Type == 3) {
		cout << "is Making";
		Helper::Display(Value);
	}
	else {
		cout << " is celebrating";
		Helper::Display(Value);
	}
	cout << endl;
}

Activity::~Activity()
{
	if (Value) delete[] Value;
}
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	int GetDay();
	int GetMonth();
	int GetYear();
	static Date CurrentDate;
	static void SetCurrentDate(int, int, int);
	void SetDate(int, int, int);
	void ReadFromFile(ifstream& fin);
	void print();
};
Date Date::CurrentDate;
Date::Date() {
	day = 0;
	month = 0;
	year = 0;
}
void Date::ReadFromFile(ifstream& fin) {
	fin >> day;
	fin >> month;
	fin >> year;

}
int Date::GetDay() {
	return day;
}
int Date::GetMonth() {
	return month;
}
int Date::GetYear() {
	return year;
}
void Date::print() {
	cout << "(" << day << "/" << month << "/" << year << ")" << endl;
}
void Date::SetCurrentDate(int d, int m, int y) {
	CurrentDate.day = d;
	CurrentDate.month = m;
	CurrentDate.year = y;
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command : \t Set Current System Date " << d << " " << m << " " << y;
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "System Date : \t" << d << "/" << m << "/" << y << endl;
}
void Date::SetDate(int d, int m, int y) {
	day = d;
	month = m;
	year = y;
}
class Post;
class Object {
protected:
	char* Id;
public:
	Object();
	virtual ~Object();
	virtual void AddPostToTimeLine(Post* id) = 0;
	virtual void PrintListView(int) = 0;
};
Object::Object() {
	Id = 0;
}
Object::~Object() {
	if (Id) {
		delete[]Id;
	}
}

class Comment {
private:
	char* Id;
	char* text;
	Object* CommentBy;
public:
	Comment();
	~Comment();
	void SetId(char*);
	void SetText(char*);
	void SetCommentBy(Object*);
	void Print(int);
};
Comment::Comment() {
	Id = 0;
	text = 0;
	CommentBy = 0;
}
Comment::~Comment() {
	if (Id) {
		delete[]Id;
	}
	if (text) {
		delete[]text;
	}
}
void Comment::SetId(char* id) {
	Id = Helper::GetStringFromBuffer(id);
}
void Comment::SetText(char* txt) {
	text = Helper::GetStringFromBuffer(txt);
}
void Comment::SetCommentBy(Object* user) {
	CommentBy = user;
}
void Comment::Print(int chk) {
	if (chk == 1) {
		CommentBy->PrintListView(1);
		cout << " wrote : ";
		Helper::Display(text);
		cout << "\"";
	}
	if (chk == 2) {
		CommentBy->PrintListView(2);
		/*	cout << "\n This";
			Helper::Display(Id);
			cout << endl;*/
		cout << " wrote : ";
		Helper::Display(text);
		cout << "\"";
	}

}
class Post {
protected:
	char* Id;
	char* Text;
	int PostType;
	int CommentCount;
	int LikesCount;
	Date SharedDate;
	Activity* activity;
	Object* SharedBy;
	Object** LikedBy;
	Comment** comments;

public:
	Post();
	~Post();
	void LoadDataFromFile(ifstream&);
	void SetSharedBy(Object*);
	int GetLikesCount();
	int GetCommentCount();
	char* GetId();
	Date GetSharedDate();
	void AddComment(Comment*);
	void AddLikedBy(Object*);
	virtual void PrintView(int chk);
	void ViewPostLikedByList();

};

Post::Post() {

	Id = 0;
	Text = 0;
	activity = 0;
	SharedBy = 0;
	LikedBy = new Object * [10];
	PostType = 0;
	comments = new Comment * [10];
	CommentCount = 0;
	LikesCount = 0;

}
Post::~Post() {
	if (Id) {
		delete[]Id;
	}
	if (Text) {
		delete[]Text;
	}
	if (activity) {
		delete activity;
	}
	if (comments) {
		for (int i = 0; i < CommentCount; i++)
			delete comments[i];
		delete[] comments;
	}

}
char* Post::GetId() {
	return Id;
}
int Post::GetLikesCount() {
	return LikesCount;
}
int Post::GetCommentCount() {
	return CommentCount;
}
Date Post::GetSharedDate() {
	//return SharedDate;

	return Date();

}
void Post::ViewPostLikedByList() {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Liked List(";
	Helper::Display(Id);
	cout << ")";
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << endl << "Post LikedBy : \n";
	for (int i = 0; i < LikesCount; i++) {
		LikedBy[i]->PrintListView(1);
		cout << endl;
	}
}
void Post::PrintView(int chk) {

	if (chk == 1) {
		if (PostType == 2) {
			activity->Print();
		}
		else {
			cout << " shared ";
		}
		cout << "\"";
		Helper::Display(Text);
		cout << "\"";
		for (int i = 0; i < CommentCount; i++) {
			cout << "\n\t\t";
			comments[i]->Print(1);
		}
		cout << endl << endl;
	}
	if (chk == 2) {
		if (PostType == 2) {
			activity->Print();
		}
		cout << "\"";
		Helper::Display(Text);
		cout << "\"";
		cout << "...";
		SharedDate.print();
		for (int i = 0; i < CommentCount; i++) {
			cout << "\n\t\t";
			comments[i]->Print(2);
		}
		cout << endl << endl;
	}
	if (chk == 3) {
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << "Command : \tView Post(" << Id << ")";
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		SharedBy->PrintListView(2);
		if (PostType == 2) {
			activity->Print();
		}
		cout << " \"";
		Helper::Display(Text);
		cout << "\"";
		cout << "...";
		SharedDate.print();
		for (int i = 0; i < CommentCount; i++) {
			cout << "\n\t\t";
			comments[i]->Print(2);
		}
		cout << endl << endl;
	}
}
void Post::AddComment(Comment* com) {
	if (CommentCount < 10) {
		comments[CommentCount] = com;
		CommentCount++;
	}
}
void Post::AddLikedBy(Object* id) {
	if (LikesCount < 10) {
		LikedBy[LikesCount] = id;
		LikesCount++;
	}
}
void Post::SetSharedBy(Object* id) {
	SharedBy = id;
}
void Post::LoadDataFromFile(ifstream& fin) {
	{
		char temp[150];
		fin >> PostType;
		fin.ignore();
		fin >> temp;
		Id = Helper::GetStringFromBuffer(temp);
		SharedDate.ReadFromFile(fin);
		fin.ignore();
		fin.getline(temp, 150);
		Text = Helper::GetStringFromBuffer(temp);
		if (PostType == 2) {
			activity = new Activity;
			activity->ReadFromFile(fin);
		}
	}
}
class Memory : public Post {
	Post* OriginalPost;
public:
	Memory();
	void SetOrignalPost(Post*, char*);
	void PrintView(int);
};
Memory::Memory() {
	OriginalPost = 0;
}
void Memory::SetOrignalPost(Post* post, char* text) {
	int idNum = 12;
	char temp[5] = "post";
	OriginalPost = post;
	Id = Helper::GetStringFromBuffer(Helper::strcat(temp, (to_string(12 + 1)).data()));
	Text = Helper::GetStringFromBuffer(text);

}
void Memory::PrintView(int temp = 0) {
	cout << " shared a memory ~~~....";
	SharedDate.SetDate(Date::CurrentDate.GetDay(), Date::CurrentDate.GetMonth(), Date::CurrentDate.GetYear());
	SharedDate.print();
	Helper::Display(Text);
	int y_dif = Date::CurrentDate.GetYear() - OriginalPost->GetSharedDate().GetYear();
	cout << "\n(" << y_dif << " Years Ago)\n";
	OriginalPost->PrintView(2);
}


class Page : public Object {
private:
	Post** TimeLine;
	int PostCount;
	char* Title;
public:
	Page();
	~Page();
	void ReadDataFromFile(ifstream& fin);
	char* GetId();
	void PrintListView(int);
	void AddPostToTimeLine(Post* id);
	Post** GetTimeLine();
	int GetPostCount();
	void ViewPage();
};
Page::Page() {
	TimeLine = new Post * [10];
	PostCount = 0;
	Id = 0;
	Title = 0;
}
Page::~Page() {
	if (Title) {
		delete[] Title;
	}
	if (TimeLine) {
		for (int i = 0; i < PostCount; i++) {
			delete TimeLine[i];
		}
		delete[]TimeLine;
	}
}
int Page::GetPostCount() {
	return PostCount;
}
Post** Page::GetTimeLine() {
	return TimeLine;
}
char* Page::GetId() {
	return Id;
}
void Page::ViewPage() {
	cout << "Command : \tView Page(" << Id << ")";
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n\n";
	Helper::Display(Title);
	cout << endl;
	for (int i = 0; i < PostCount; i++) {
		Helper::Display(Title);
		cout << " ";
		TimeLine[i]->PrintView(2);
	}
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";

}
void Page::PrintListView(int chk) {
	if (chk == 1) {
		Helper::Display(Id);
		cout << " - ";
		Helper::Display(Title);
	}
	if (chk == 2) {
		cout << " --- ";
		Helper::Display(Title);
	}
}
void Page::ReadDataFromFile(ifstream& fin) {
	char temp[50];
	fin >> temp;
	Id = Helper::GetStringFromBuffer(temp);
	fin.getline(temp, 50);
	Title = Helper::GetStringFromBuffer(temp);
}
void Page::AddPostToTimeLine(Post* id) {
	if (PostCount < 10) {
		TimeLine[PostCount] = new Post;
		TimeLine[PostCount] = id;
		PostCount++;
	}
}
class User : public Object {
private:

	char* Fname;
	char* Lname;
	int LikedPagesCount;
	int FriendsCount;
	int PostCount;
	Post** TimeLine;
	Page** LikedPages;
	User** FriendList;

public:
	User();
	~User();
	int TotalComment;
	void ReadDataFromFile(ifstream& fin);
	void AddLikedPages(Page*);
	void AddFriend(User*);
	char* GetId();
	void ViewFriendList();
	void PrintListView(int);
	void ViewLikedPages();
	void AddPostToTimeLine(Post*);
	void ViewHome();
	void ViewTimeLine();
	void LikePost(Post*);
	void AddNewComment(Post*, char*);
	void ShareMemory(Post*, char*);
	void SeeYourMemories();
};
User::User() {
	Id = 0;
	Fname = 0;
	Lname = 0;
	LikedPages = new Page * [10];
	FriendList = new User * [10];
	for (int i = 0; i < 10; i++)
		FriendList[i] = 0;
	TimeLine = new Post * [10];
	LikedPagesCount = 0;
	FriendsCount = 0;
	PostCount = 0;
	TotalComment = 13;
}
User :: ~User() {
	if (Fname) {
		delete[] Fname;
	}
	if (Lname) {
		delete[] Lname;
	}
	if (LikedPages) {
		delete[] LikedPages;
	}
	if (FriendList) {
		delete[] FriendList;
	}
	if (TimeLine) {
		for (int i = 0; i < PostCount; i++) {
			delete TimeLine[i];
		}
		delete[] TimeLine;
	}
}
void User::SeeYourMemories() {
	bool flag = false;
	int year_diff = 0;
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tSee Your Memories\n------------------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < FriendsCount; i++) {
		if (TimeLine[i]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago\n";
		for (int i = 0; i < FriendsCount; i++) {
			if (TimeLine[i]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay()) {
				cout << "\nOn this Day\n";
				year_diff = Date::CurrentDate.GetYear() - TimeLine[i]->GetSharedDate().GetYear();
				cout << year_diff << " Years Ago\n";
				Helper::Display(Fname);
				cout << " ";
				Helper::Display(Lname);
				TimeLine[i]->PrintView(2);

			}
		}
	}
	else {
		cout << "\nThere is No Memories Shared On this day in Past Years\n";
	}
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
}
void User::ShareMemory(Post* post, char* text) {
	cout << "Command : \t Share Memory(";
	Helper::Display(post->GetId());
	cout << ",";
	Helper::Display(text);
	cout << ")";
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	Memory* temp;
	temp = new Memory;
	temp->SetOrignalPost(post, text);
	TimeLine[PostCount] = temp;
	PostCount++;
}
void User::LikePost(Post* post) {
	int chk = post->GetLikesCount();
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command : Like Post (";
	cout << post->GetId();
	cout << ")";
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	if (chk > 10) {
		cout << "Maximum Likes Reached \n";
	}
	else {
		post->AddLikedBy(this);
	}
}
void User::AddNewComment(Post* post, char* text) {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command : \tPost Comment(" << post->GetId() << ",";
	Helper::Display(text);
	cout << ")";
	int chk = post->GetCommentCount();
	TotalComment++;
	string temp = to_string(TotalComment);
	int len;
	for (int i = 0; temp[i] != '\0'; i++) {
		len = i;
	}

	char* IdNum = new char[len + 1];
	for (int i = 0; i < len + 1; i++) {
		IdNum[i] = temp[i];
	}
	IdNum[len + 1] = '\0';
	char id[2] = "c";
	char* Id = Helper::strcat(id, IdNum);
	Comment* comment = new Comment;
	comment->SetText(text);
	comment->SetCommentBy(this);
	comment->SetId(Id);
	if (chk > 10) {
		cout << "Maximum Comments Reached \n";
	}
	else {
		post->AddComment(comment);
	}

}
void User::ViewTimeLine() {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView TimeLine\n------------------------------------------------------------------------------------------------------------------------\n";
	Helper::Display(Fname);
	cout << " ";
	Helper::Display(Lname);
	cout << "  -  TimeLine\n\n";

	for (int i = 0; i < PostCount; i++) {
		Helper::Display(Fname);
		cout << " ";
		Helper::Display(Lname);
		TimeLine[i]->PrintView(2);
	}
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";

}
void User::ViewHome() {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Home\n------------------------------------------------------------------------------------------------------------------------\n";
	Helper::Display(Fname);
	cout << " ";
	Helper::Display(Lname);
	cout << "  -  Home Page\n\n";
	for (int i = 0; i < FriendsCount; i++) {
		for (int j = 0; j < FriendList[i]->PostCount; j++) {
			if ((FriendList[i]->TimeLine[j]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay() - 1 && FriendList[i]->TimeLine[j]->GetSharedDate().GetMonth() == Date::CurrentDate.GetMonth() && FriendList[i]->TimeLine[j]->GetSharedDate().GetYear() == Date::CurrentDate.GetYear()) || (FriendList[i]->TimeLine[j]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay() && FriendList[i]->TimeLine[j]->GetSharedDate().GetMonth() == Date::CurrentDate.GetMonth() && FriendList[i]->TimeLine[j]->GetSharedDate().GetYear() == Date::CurrentDate.GetYear())) {
				FriendList[i]->PrintListView(2);
				FriendList[i]->TimeLine[j]->PrintView(1);

			}
		}
	}
	for (int i = 0; i < LikedPagesCount - 1; i++) {
		for (int j = 0; j < LikedPages[i]->GetPostCount(); j++) {
			if ((LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay() - 1 && LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetMonth() == Date::CurrentDate.GetMonth() && LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetYear() == Date::CurrentDate.GetYear()) || (LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetDay() == Date::CurrentDate.GetDay() && LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetMonth() == Date::CurrentDate.GetMonth() && LikedPages[i]->GetTimeLine()[j]->GetSharedDate().GetYear() == Date::CurrentDate.GetYear())) {
				LikedPages[i]->PrintListView(2);
				LikedPages[i]->GetTimeLine()[j]->PrintView(1);
			}
		}
	}
}
void User::ViewFriendList() {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tSet Current User \"";
	Helper::Display(Id);
	cout << "\"";
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	Helper::Display(Fname);
	cout << " ";
	Helper::Display(Lname);
	cout << " successfully set as Current User\n\n";
	cout << "Command:\tView Friend List\n------------------------------------------------------------------------------------------------------------------------\n";
	Helper::Display(Fname);
	cout << " ";
	Helper::Display(Lname);
	cout << " - Friend List" << endl << endl;


	for (int i = 0; i < FriendsCount; i++) {
		if (FriendList[i]->GetId()[0] != '-') {
			Helper::Display(FriendList[i]->GetId());
			FriendList[i]->PrintListView(2);
			cout << endl;
		}
	}
}
void User::ViewLikedPages() {
	cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Liked Pages\n------------------------------------------------------------------------------------------------------------------------\n";
	Helper::Display(Fname);
	cout << " ";
	Helper::Display(Lname);
	cout << " - Liked Pages" << endl << endl;
	for (int i = 0; i < LikedPagesCount - 1; i++) {
		if (LikedPages[i]->GetId()[0] != '-') {
			LikedPages[i]->PrintListView(1);
			cout << endl;
		}
	}
}
void User::PrintListView(int chk) {
	if (chk == 1) {
		Helper::Display(Id);
		cout << " - ";
		Helper::Display(Fname);
		cout << " ";
		Helper::Display(Lname);
	}
	if (chk == 2) {
		cout << " --- ";
		Helper::Display(Fname);
		cout << " ";
		Helper::Display(Lname);
	}

}
char* User::GetId() {
	return Id;
}
void User::AddFriend(User* id) {
	if (FriendsCount < 10) {
		FriendList[FriendsCount] = new User;
		FriendList[FriendsCount] = id;
		FriendsCount++;
	}
}
void User::AddLikedPages(Page* id) {
	if (LikedPagesCount < 10) {
		LikedPages[LikedPagesCount] = new Page;
		LikedPages[LikedPagesCount] = id;
		LikedPagesCount++;
	}
}
void User::AddPostToTimeLine(Post* id) {
	if (PostCount < 10) {
		TimeLine[PostCount] = new Post;
		TimeLine[PostCount] = id;
		PostCount++;
	}
}
void User::ReadDataFromFile(ifstream& fin) {
	char temp[20];
	fin >> temp;
	Id = Helper::GetStringFromBuffer(temp);
	fin >> temp;
	fin.ignore();
	Fname = Helper::GetStringFromBuffer(temp);
	fin >> temp;
	Lname = Helper::GetStringFromBuffer(temp);


}

class Fb {
private:
	Page** pages;
	User** users;
	Post** posts;
	int TotalPages;
	int TotalUser;
	int TotalPost;
	int TotalComment;
public:
	Fb();
	~Fb();
	Page* SearchPageById(char* id);
	User* SearchUserById(char* id);
	Object* SearchObjectById(char* id);
	Post* SearchPostById(char*);
	void LikePost(Post*);
	void LoadPagesFromFile();
	void LoadUserFromFile();
	void LoadPost();
	void LoadComment();
	void Load();
};
Fb::Fb() {
	pages = 0;
	users = 0;
	TotalPages = 0;
	TotalUser = 0;
	TotalComment = 0;
}
Fb :: ~Fb() {
	if (pages) {
		for (int i = 0; i < TotalPages; i++) {
			delete pages[i];
		}
		delete[] pages;
	}
	if (users) {
		for (int i = 0; i < TotalUser; i++) {
			delete users[i];
		}
		delete[] users;
	}
	if (posts) {
		delete[] posts;
	}
}
Page* Fb::SearchPageById(char* id) {
	for (int i = 0; i < TotalPages; i++) {
		if (Helper::MatchString(pages[i]->GetId(), id)) {
			return pages[i];
		}
	}
}
User* Fb::SearchUserById(char* id) {

	for (int i = 0; i < TotalUser; i++) {
		if (Helper::MatchString(users[i]->GetId(), id)) {
			return users[i];
		}
	}
}
Post* Fb::SearchPostById(char* id) {
	for (int i = 0; i < TotalPost; i++) {
		if (Helper::MatchString(posts[i]->GetId(), id)) {
			return posts[i];
		}
	}
	return nullptr;
}
Object* Fb::SearchObjectById(char* id) {
	Object* temp;
	if (id[0] == 'p') {
		temp = SearchPageById(id);
	}
	else {
		temp = SearchUserById(id);
	}
	return temp;

}
void Fb::Load() {
	LoadPagesFromFile();
	LoadUserFromFile();
	LoadPost();
	LoadComment();
}
void Fb::LoadComment() {

	ifstream fin("Comments.txt");
	if (fin) {
		fin >> TotalComment;
		char temp[50];
		char* CommentID;
		char* postId;
		char temp_CommentBy[10];
		char text[100];
		for (int i = 0; i < TotalComment + 1; i++)
		{
			Comment* comment = new Comment;
			fin >> temp;
			CommentID = Helper::GetStringFromBuffer(temp);
			fin >> temp;
			postId = Helper::GetStringFromBuffer(temp);
			Post* postPtr = SearchPostById(postId);
			postPtr->AddComment(comment);
			fin >> temp_CommentBy;
			Object* CommentBy = SearchObjectById(temp_CommentBy);
			fin.getline(text, 100);
			comment->SetId(CommentID);
			comment->SetText(text);
			comment->SetCommentBy(CommentBy);
		}
		fin.close();
	}
	else {
		cout << "Comments File doesnot exist";
	}

}
void Fb::LoadPost() {

	char temp[20];
	ifstream fin("Posts.txt");
	if (fin) {
		fin >> TotalPost;
		posts = new Post * [TotalPost];
		for (int i = 0; i < TotalPost; i++) {
			bool flag = true;
			posts[i] = new Post;
			posts[i]->LoadDataFromFile(fin);
			fin >> temp;
			Object* sharedBy = SearchObjectById(temp);
			posts[i]->SetSharedBy(sharedBy);
			sharedBy->AddPostToTimeLine(posts[i]);
			fin >> temp;
			if (temp[0] != '-') {
				Object* LikedBy = SearchObjectById(temp);
				posts[i]->AddLikedBy(LikedBy);
				while (flag) {

					fin >> temp;
					if (temp[0] == '-') {
						flag = false;
					}
					else {
						LikedBy = SearchObjectById(temp);
						posts[i]->AddLikedBy(LikedBy);
					}
				}
			}
		}
		fin.close();
	}
	else {
		cout << "Posts File doesnot exist";
	}

}
void Fb::LoadPagesFromFile() {
	ifstream fin("Pages.txt");
	if (fin) {
		fin >> TotalPages;
		pages = new Page * [TotalPages];
		for (int i = 0; i < TotalPages; i++) {
			pages[i] = new Page;
			pages[i]->ReadDataFromFile(fin);
			char temp[50];
		}
		fin.close();
	}
	else {
		cout << "Pages File doesnot exist";
	}
}
void Fb::LoadUserFromFile() {
	ifstream fin("User.txt");
	if (fin) {
		char*** temp_user;
		fin >> TotalUser;
		temp_user = new char** [TotalUser];
		for (int i = 0; i < TotalUser; i++) {
			temp_user[i] = new char* [11];
			for (int j = 0; j < 11; j++) {
				temp_user[i][j] = new char[4];
			}
		}

		users = new User * [TotalUser];
		for (int i = 0; i < TotalUser; i++) {
			users[i] = new User;
			users[i]->ReadDataFromFile(fin);
			char temp[20];
			int j = 0;
			fin >> temp;
			if (temp[0] != '-') {
				temp_user[i][j] = Helper::GetStringFromBuffer(temp);

				while (temp[0] != '-') {
					j++;
					fin >> temp;
					temp_user[i][j] = Helper::GetStringFromBuffer(temp);

				}
				j++;
				temp_user[i][j] = Helper::GetStringFromBuffer(temp);
			}
			else {
				temp_user[i][j] = Helper::GetStringFromBuffer(temp);
			}

			char* pagesId = 0;
			fin >> temp;
			if (temp[0] != '-') {
				pagesId = Helper::GetStringFromBuffer(temp);
				users[i]->AddLikedPages(SearchPageById(pagesId));
				while (temp[0] != '-') {
					fin >> temp;
					pagesId = Helper::GetStringFromBuffer(temp);
					users[i]->AddLikedPages(SearchPageById(pagesId));

				}
			}
		}
		//Adding Friends to Friends List
		for (int i = 0; i < TotalUser; i++) {
			for (int j = 0; j < 11; j++) {
				if (temp_user[i][j][0] == '-')
					break;
				users[i]->AddFriend(SearchUserById(temp_user[i][j]));
			}
		}
		fin.close();
		//Deletion
		for (int i = 0; i < TotalUser; i++) {
			for (int j = 0; j < 11; j++) {
				delete[] temp_user[i][j];
			}
			delete[] temp_user[i];
		}
		delete[] temp_user;
	}
	else {
		cout << "Users File doesnot exist";
	}
}
int main() {

	Fb fb;
	fb.Load();
	char user[4] = "u14";
	User* CurrentUser = fb.SearchUserById(user);
	Date::SetCurrentDate(15, 11, 2017);
	CurrentUser->ViewFriendList();
	CurrentUser->ViewLikedPages();
	CurrentUser->ViewHome();
	CurrentUser->ViewTimeLine();
	char post5[6] = "post5";
	Post* PostToBeLike = fb.SearchPostById(post5);
	PostToBeLike->ViewPostLikedByList();
	CurrentUser->LikePost(PostToBeLike);
	PostToBeLike->ViewPostLikedByList();
	char comment_1[100] = "Good Luck for your Result";
	char post4[6] = "post5";
	Post* PostToBeComment = fb.SearchPostById(post4);
	CurrentUser->AddNewComment(PostToBeComment, comment_1);
	PostToBeComment->PrintView(3);
	char comment_2[100] = "Thanks for the wishes";
	char post8[6] = "post8";
	PostToBeComment = fb.SearchPostById(post8);
	CurrentUser->AddNewComment(PostToBeComment, comment_2);
	PostToBeComment->PrintView(3);
	char post10[7] = "post10";
	Post* PostToShareMemory = fb.SearchPostById(post10);
	char text[100] = "\"Never thought I will be specialist in this field...\"";
	CurrentUser->SeeYourMemories();
	CurrentUser->ShareMemory(PostToShareMemory, text);
	CurrentUser->ViewTimeLine();
	char page1[3] = "p1";
	Page* p1 = fb.SearchPageById(page1);
	p1->ViewPage();

	return 0;
}


