/*DORWTHEOS KOUGIAS
AM: 2022202500064
dit25064@go.uop.gr

VASILHS VARTHOLOMAIOS
AM: 2022202500064
dit25175@go.uop.gr
*/

/*
 * =============================================================
 * TITLE:               Zombiecide
 * VERSION:             1.0.0
 * CONTRIBUTING DEVELOPERS: Vasilhs Vartholomaios - Dorothews Kougias
 * ALBUM:               Project Game
 * DATE COMPILED:       02-05-2026
 * =============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#define MAXR 10
#define MAXC 10
#define points_of_zombie 2
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define BRIGHT_RED "\033[38;2;212;0;0m" 
#define GREEN "\033[1;32m" 
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m" 
#define MAGENTA "\033[1;35m" 
#define CYAN "\033[1;36m"
#define BRICK "\033[38;5;124m"
#define ORANGE "\033[38;5;208m"
#define SKY_BLUE "\033[38;5;39m"
#define ORCHID "\033[38;5;170m"
#define GRAY "\033[38;5;244m"
int check(char **table, int row, int cols);
void free_table(char **table, int row);
void table1(char **table,int row,int col,int zombies);
void houses(char **table, int *maxbuilding,int row, int col);
void guns(char **table,int row,int cols,int zombies,int sound_dir,int course,int **map);
void plasmagun(char **table,int row,int cols,int sound_dir);
void bombing(char **table,int row,int cols,int zombies,int sound_dir);
int neurogun(char **table,int row,int cols,int r,int c,char type,int **map);
void give_neurogun(char **table,int row,int cols,int sound_dir,int **map);
void welcome();
void logout(int course,double seconds);
int zombie();
char **array(int row,int cols);
void coordinates(int *row,int *cols);
void print_table(char **table,int row,int col);
void move_zombies(char **table, int sound_dir,int row,int cols);
int sound_direction();
void FAQ();
char question_FAQ();
void warning(char **table,int row,int cols);
void print_table1(char **table,int row,int col);
void system_clear();
int total_score=0;
int zombies_kill=0;
time_t start_time;
char extra;
int main()
{
    int row,cols,zombies,ch=0,sound_dir;
    char **table,answer;
	double seconds;
	int **map,i;
    int course=1; // gia na jekinaei apo thn prwth pista
    srand((unsigned int)time(NULL));
	start_time = time(NULL); // apothikeuei ton xrono se deuterolepta apo ths 1/1/1970
	printf(GREEN"Do you want to have the extra resources?\n"RESET);
	do{
		scanf(" %c",&extra);
		if (tolower(extra) != 'y' && tolower(extra) != 'n'){
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			printf (RED"Wrong value\n"RESET);
		}
	}while(tolower(extra) != 'y' && tolower(extra) != 'n');
	welcome();
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './welcome.wav').PlaySync()\""); // paizei mia fora
        	system("start /min powershell -WindowStyle Hidden -Command \"while($true) { (New-Object Media.SoundPlayer './soundtrack1.wav').PlaySync() }\""); // paizei se atermon vroxo
    	#else // six seven
        	system("paplay welcome.wav"); // paizei mia fora
        	system("(while true; do command -v paplay >/dev/null && paplay soundtrack1.wav || break; done) >/dev/null 2>&1 &"); // paizei se atermon vroxo
    	#endif
	}
	//---------------------question FAQ------------------------------------
	do {
    	answer = question_FAQ();
    	if (answer == 'y')
    	    FAQ();
	} while (answer != 'n');
	//---------------------eksodos syntetagmenon-------------------------------
	coordinates(&row,&cols);
	// --------------------dhmiourgia pinaka--------------------------------------
	table = array(row,cols);
	// --------------------dhmiourgia map-----------------------------------------
	map = (int**)malloc((size_t)row * sizeof(int*));
	if (map == NULL){
		printf(RED"Out of space\n"RESET); 
		exit(1);
	}
	for (i=0;i<row;i++){
		map[i] = (int*)calloc((size_t)cols, sizeof(int));
		if (map[i] == NULL){ 
			printf(RED"Out of space\n"RESET); 
			exit(1); 
		}
	}
    //---------------------eksodos zombies----------------------------------------
    zombies = zombie();
	while (row < MAXR && cols < MAXC)
	{
		table1(table,row,cols,zombies);
        sound_dir = sound_direction();
        while(1)
		{
			//-------------------out for guns----------------------------------------
			guns(table,row,cols,zombies,sound_dir,course,map);
			ch = check(table,row,cols);
			if(ch == 1)
			{
				if (tolower(extra) == 'y'){
					system_clear();
					printf(MAGENTA);
					welcome();
				}
				printf(YELLOW);
				printf ("\n===========================\n");
				printf("          NEW LEVEL         \n");
				printf ("===========================\n\n");
				printf(RESET);
                break;
			}
		}
		free_table(table,row); // eleutherosei mnhmhs tou pinaka table
		// eleutherosei map
		for (i=0;i<row;i++) 
			free(map[i]);
		free(map);
		course++; // gia na metrame poses pistes exei paijei o paikths
        if(row<MAXR)
			row++;
		if(cols<MAXC)
			cols++;
		table = array(row,cols);
		// epanekxorisi map me nea diastasi
		map = (int**)malloc((size_t)row * sizeof(int*));
		if (map == NULL){
			printf(RED"Out of space\n"RESET);
            printf("\a");
            exit(1);
        }
			for (i=0;i<row;i++){
				map[i] = (int*)calloc((size_t)cols, sizeof(int));
				if (map[i] == NULL){
					printf(RED"Out of space\n"RESET);
                    printf("\a"); 
                    exit(1);
                }
			}
	}
	time_t current_time = time(NULL); //apothiekuei ton xrono apo tis 1/1/1970 alla twra gia otan teleiwsei to programma
	seconds = difftime(current_time,start_time); // aferei tous dio xronous kai vriskeis posa deuterolepta paizei o paikths
	logout(course,seconds);
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
    		system("taskkill /f /im powershell.exe"); // gia na kleisei oti trexei
		#else
    		system("pkill -9 pwsh"); 
		#endif
	}
	return 0;
}

void system_clear(){
	#ifdef _WIN32 // gia na einai compatible se ola ta logismika 
		system("cls");
	#else
		system("clear");
	#endif
}

void user(){
	#ifdef _WIN32
        printf("USER: "); 
		system("echo %USERNAME%");
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system
        printf("[TIME]: "); 
		system("time /t");
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system
        printf("[DATE]: "); 
		system("date /t");
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system
    #else
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system
		system("whoami");
        printf("[TIME]: "); 
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system
		system("date +%H:%M"); // mono h wra
        printf("[DATE]: ");
		fflush(stdout); //gia na adeiasei to buffer ths printf prin thn system 
		system("date +%Y-%m-%d"); // mono h hmeromhnia
    #endif

}

void welcome(){
	if (tolower(extra) == 'y')
		system_clear();
	printf(MAGENTA);
	printf("====================================================\n");
    printf("                WELCOME IN ZOMBIECIDE:              \n");
    printf("====================================================\n");
    printf("\n[STATUS]: User Login: ");
	user();
	printf("====================================================\n\n");
	printf(RESET);
}

void logout(int course,double seconds){
	if (tolower(extra) == 'y')
		system_clear();
	printf(CYAN"[PLAYTIME]: %d minutes %d seconds\n",(int)seconds/60,(int)seconds%60);
	printf(GREEN"[TOTAL POINTS]: %d\n",total_score);
    printf (ORANGE"[COURSES]: %d\n",course);
	printf(BRIGHT_RED"[TOTAL ZOMBIES KILL]: %d\n"MAGENTA,zombies_kill);
	printf("====================================================\n");
	printf("          LOGGING OUT FROM ZOMBIECIDE               \n");
	printf("====================================================\n");
	printf("\n[STATUS]: User Logout: ");
	user();
	printf("====================================================\n\n");
	printf(RESET);
}

void coordinates(int *row,int *cols){
    printf (GRAY"Give me the cordinates: \n"RESET);
    do {
        scanf ("%d",row);
        while (getchar() != '\n'); // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
        if (*row <= 0 || *row >= MAXR){
			printf (RED"Wrong values\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}
    while (*row <= 0 || *row >= MAXR);
	do {
        scanf ("%d",cols);
        while (getchar() != '\n'); // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
       	if (*cols <= 0 || *cols >= MAXC){
			printf (RED"Wrong values\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}
    while (*cols <= 0 || *cols >= MAXC);
}

char **array(int row,int cols){
	int i;
	char **table = (char**)malloc((size_t)row * sizeof(char*)); // dimiourgia pinaka
	if (table == NULL){
		printf (RED"Out of space\n"RESET);
		printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		exit(1);
	}
	for (i=0;i<row;i++)
	{
		table[i] = (char*)malloc(sizeof(char)*(size_t)cols);
		if (table[i] ==  NULL){
			printf (RED"Out of space\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			exit(1);
		}	
	}
	return table;
}

int zombie(){
	int zombies;
	printf (GRAY"How many different type of zombies do you want: \n"RESET);
	do{
		scanf ("%d",&zombies);
        while (getchar() != '\n') // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
			; //gia na mhn vgazei warning to -Wextra
		if (zombies <= 0 || zombies > 9){
			printf (RED"Wrong values\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}
	while (zombies <= 0 || zombies > 9);
	return zombies;
}

void table1(char **table,int row,int col,int zombies){
    int i,maxbuilding,m,j,k=1;
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './zombie.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay zombie.wav");
    	#else
        	system("paplay zombie.wav");
   		#endif
		system_clear();
		welcome();
	}
	printf(CYAN);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			table[i][j] = (char)(1+rand()%zombies);
	maxbuilding = (row*col)/8;
	while (maxbuilding > 0)
		houses(table,&maxbuilding,row,col);
	for(i=0;i<row+2;i++)
	{
		if(i==0)
		{
			for(m=0;m<col;m++)
			{
				if(m==0)
				{
					printf("%4d", k);
					k++;
				}
				else
				{
					printf("%2d", k);
					k++;
				}
			}
		k = 0;
		}
		else if(i==1)
		{
			for(m=0;m<col * 2-1+3;m++)
				printf("-");
		}
		else
		{
			printf("%d| ", i-1);
			for(j=1;j<col+1;j++)
			{
				if(table[i-2][j-1] !=35)
					printf("%d ", table[i-2][j-1]);
				else{
					printf(BRICK);
					printf("# ");
					printf(CYAN);
				}
			}
		}
		printf("\n");
	}
	printf(RESET);
}

void houses(char **table, int *maxbuilding, int row, int cols) {
    int ri,rj,stop,l,dir1,dir2;
	while(1)
	{
		ri = rand()%row;
		rj = rand()%cols;
		if (table[ri][rj] != '#')
		{
			table[ri][rj] = '#';
			(*maxbuilding)--;
			break;
		}
	}
	dir1 = rand()%2; /* directions  row = 0 col = 1 */
	stop = 1;
	while(stop && *maxbuilding > 0)
	{
		if(dir1 == 0) /*move row*/
		{
			if(rj==0)
			{
				rj++; /* mono dejia mporei na paei xoris na bgei ektos pinaka */
				if(table[ri][rj] != '#')
				{
					table[ri][rj] = '#';
					(*maxbuilding)--;
				}
				l = rand()%3;
				if(l == 0) /* an h rand ferei 0 tote stamataei na bazei kthria mazi */
					stop = 0;
			}
			else if(rj==cols-1)
            {
                                rj--; /* mono aristera mporei na paei xoris na bgei ektos pinaka */
				if(table[ri][rj] != '#')
				{
                    table[ri][rj] = '#';
                    (*maxbuilding)--;
				}
                l = rand()%3;
                if(l == 0)
                    stop = 0;
            }
			else
			{
				dir2 = rand()%2; /* left = 0 right = 1 */
				if(dir2 == 0)
				{
					rj--;
					if(table[ri][rj] != '#')
					{
						table[ri][rj] = '#';
						(*maxbuilding)--;
					}
					l = rand()%3;
					if(l == 0)
						stop = 0;
				}
				else if(dir2 == 1)
                {
                    rj++;
					if(table[ri][rj] != '#')
					{
                        table[ri][rj] = '#';
                        (*maxbuilding)--;
					}
                    l = rand()%3;
                    if(l == 0)
                        stop = 0;
                }
			}
		}
		if(dir1 == 1) /*move col*/
        {
            if(ri==0)
            {
                ri++; /* mono dejia mporei na paei xoris na bgei ektos pinaka */
				if(table[ri][rj] != '#')
				{
                    table[ri][rj] = '#';
                    (*maxbuilding)--;
                }
				l = rand()%3;
                if(l == 0) /* an h rand ferei 0 tote stamataei na bazei kthria mazi */
                    stop = 0;
            }
            else if(ri==row-1)
            {
                ri--; /* mono aristera mporei na paei xoris na bgei ektos pinaka */
                if(table[ri][rj] != '#')
				{
					table[ri][rj] = '#';
                    (*maxbuilding)--;
				}
                l = rand()%3;
                if(l == 0)
                    stop = 0;
            }
			else
            {
                dir2 = rand()%2; /* up = 0 down = 1 */
                if(dir2 == 0)
                {
                    ri--;
					if(table[ri][rj] != '#')
					{
                        table[ri][rj] = '#';
                        (*maxbuilding)--;
					}
                    l = rand()%3;
                    if(l == 0)
                        stop = 0;
                }
                else if(dir2 == 1)
                {
                    ri++;
					if(table[ri][rj] != '#')
					{
                        table[ri][rj] = '#';
                        (*maxbuilding)--;
					}
                    l = rand()%3;
                    if(l == 0)
                        stop = 0;
                }
            }
        }
	}
}

void print_table(char **table,int row,int cols){
    int i,m,j,k=1;
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './zombie.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay zombie.wav");
    	#else
        	system("paplay zombie.wav");
    	#endif
		welcome();
	}
	printf(CYAN);
	for(i=0;i<row+2;i++)
	{
		if(i==0)
		{
			for(m=0;m<cols;m++)
			{
				if(m==0)
				{
					printf("%4d", k);
					k++;
				}
				else
				{
					printf("%2d", k);
					k++;
				}
			}
		k = 0;
		}
		else if(i==1)
			for(m=0;m<cols*2-1+3;m++)
				printf("-");
		else
		{
			printf("%d| ", i-1);
			for(j=1;j<cols+1;j++)
				if (table[i-2][j-1] == 35){
                    printf(BRICK);
					printf("# ");
					printf(CYAN);
				}
                else if (table[i-2][j-1] == 46){
                    printf(ORANGE);
					printf(". ");
					printf(CYAN);
				}
                else
                    printf("%d ", table[i-2][j-1]);
		}
        printf("\n");
	}
	printf(RESET);
	k = rand()%10;
	if (k == 1)
		warning(table,row,cols);
}

void print_table1(char **table,int row,int cols){
    int i,m,j,k=1;
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './zombie.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay zombie.wav");
    	#else
        	system("paplay zombie.wav");
    	#endif
	}
	printf(CYAN"\n");
	for(i=0;i<row+2;i++)
	{
		if(i==0)
		{
			for(m=0;m<cols;m++)
			{
				if(m==0)
				{
					printf("%4d", k);
					k++;
				}
				else
				{
					printf("%2d", k);
					k++;
				}
			}
		k = 0;
		}
		else if(i==1)
			for(m=0;m<cols*2-1+3;m++)
				printf("-");
		else
		{
			printf("%d| ", i-1);
			for(j=1;j<cols+1;j++)
				if (table[i-2][j-1] == 35){
                    printf(BRICK);
					printf("# ");
					printf(CYAN);
				}
                else if (table[i-2][j-1] == 46){
                    printf(ORANGE);
					printf(". ");
					printf(CYAN);
				}
                else
                    printf("%d ", table[i-2][j-1]);
		}
        printf("\n");
	}
	printf(RESET);
}

void warning(char **table,int row,int cols){
	if (tolower(extra) == 'y'){
		int i;
		system_clear();
		printf(BRIGHT_RED"WARNING: SYSTEM INFECTED\n"RESET);
		for (i=0;i<20;i++)
			printf("CRITICAL ERROR: MEMORY LEAK AT 0x%X...\n", rand()); // %X emfanizei enan arithmo sto dekaejadiko systhma
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './nothing.wav').PlaySync()\"");
			system("powershell -c \"(New-Object Media.SoundPlayer './nothing.wav').PlaySync()\""); // enas hxos pou den paizei kati apla gia na kathisterhsei gia 1 sec
    	#elif __APPLE__
        	system("afplay nothing.wav");
			system("afplay nothing.wav");
    	#else
        	system("paplay nothing.wav");
			system("paplay nothing.wav");
    	#endif // enas hxos pou den paizei kati apla gia na kathisterhsei gia 1 sec
		system_clear();
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './nothing.wav').PlaySync()\"");
    	#elif __APPLE__
        system("afplay nothing.wav");
    	#else
        	system("paplay nothing.wav");
    	#endif // enas hxos pou den paizei kati apla gia na kathisterhsei gia 1 sec
		printf(BRIGHT_RED);
		printf(" d888888b  db   db  d88888b  db    db      .d8b.   d8888b.  d88888b      .d888b.   .d888b.  .88b  d88.  d888888b  d8b   db   .d88b.  \n");
    	printf(" `~~88~~'  88   88  88'      `8b  d8'     d8' `8b  88  `8D  88'          88'      88' `8D  88'YbdP`88    `88'    888o  88  .8P  Y8. \n");
    	printf("    88     88ooo88  88ooooo   `8bd8'      88ooo88  88oobY'  88ooooo      88       88   88  88  88  88     88     88V8o 88  88    88 \n");
    	printf("    88     88~~~88  88~~~~~     88        88~~~88  88`8b    88~~~~~      88       88   88  88  88  88     88     88 V8o88  88    88 \n");
    	printf("    88     88   88  88.         88        88   88  88 `88.  88.          88.      88. .8D  88  88  88    .88.    88  V888  `8b  d8' \n");
    	printf("    YP     YP   YP  Y88888P     YP        YP   YP  88   YD  Y88888P      `888P'   `888P'   YP  YP  YP  Y888888P  VP   V8P   `Y88P'  \n"RESET);
		print_table1(table,row,cols);
	}
}

void guns(char **table,int row,int cols,int zombies,int sound_dir,int course,int **map){
	char oplo;
	double seconds;
	int i;
	// h synarthsei tolower() metatrepei ena kefalaio gramma se mikro diladi to P --> to metatrepei se p
	printf (GRAY"Give me the weapon you want to use:\n"RESET);
	do{
		scanf(" %c",&oplo);
        while (getchar() != '\n') // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
			; // gia na mhn vgazei warning to -Wextra
		if (tolower(oplo) != 'p' && tolower(oplo) != 'b' && tolower(oplo) !='n' && tolower(oplo) !='x'){
			printf (RED"Wrong value for weapon\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}while (tolower(oplo)!='p' && tolower(oplo)!='b' && tolower(oplo)!='n' && tolower(oplo)!='x');
	switch(tolower(oplo)){
        case 'p':
		    plasmagun(table,row,cols,sound_dir);
            break;
	    case 'b':
		    bombing(table,row,cols,zombies,sound_dir);
            break;
	    case 'n':
			give_neurogun(table,row,cols,sound_dir,map);
            break;
	    case 'x':
			time_t current_time = time(NULL); //apothiekuei ton xrono apo tis 1/1/1970 alla twra gia otan teleiwsei to programma
			seconds = difftime(current_time,start_time); // aferei tous dio xronous kai vriskeis posa deuterolepta paizei o paikths
			if (course == 1)
            	logout(course,seconds);
			else 
				logout(course-1,seconds); // course-1 gia na mhn metrhsh thn kainourgia pista thn opoia den oloklhrwse
		    free_table(table,row); // eleutherosei mnhmhs tou pinaka table
			for (i=0;i<row;i++) 
				free(map[i]);
			free(map);		   
			if (tolower(extra) == 'y'){
				#ifdef _WIN32
    				system("taskkill /f /im powershell.exe"); // gia na kleisei oti trexei
				#else
    				system("pkill -9 pwsh"); 
				#endif
			}
		    exit(0); //gia na teleiwnei to programma to leei paragrafos 4.
    }
}

void plasmagun(char **table,int row,int cols,int sound_dir){
	char thesi;
	int stoixeio,i,sum,score;
	printf(GREEN"[ACTION]: You picked up the plasmagun\n");
	printf (GRAY"Give me the side of which the plasmagun will be used\n"RESET);
	do{
		scanf (" %c",&thesi);
        while (getchar() != '\n') // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
			; // gia na mhn vgazei warning to -Wextra
		if (tolower(thesi) != 'l'&& tolower(thesi) != 'r' && tolower(thesi) != 'u' && tolower(thesi) != 'd'){
			printf (RED"Wrong values for the position\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}while (tolower(thesi) != 'l'&& tolower(thesi) != 'r' && tolower(thesi) != 'u' && tolower(thesi) != 'd');
	printf (GRAY"Give me the coordinates for the plasmagun:\n"RESET);
	do{
		scanf ("%d",&stoixeio);
        while (getchar() != '\n') // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
			; // gia na mhn vgazei warning to -Wextra
		if (tolower(thesi) == 'u' || tolower(thesi) == 'd'){
			if (stoixeio > cols || stoixeio <=0){
				printf (RED"Element outside the table boundaries\n"RESET);
				printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			}
		}
		else if(tolower(thesi) == 'l' || tolower(thesi) == 'r'){
			if (stoixeio > row || stoixeio <=0){
				printf (RED"Element outside the table boundaries\n"RESET);
			    printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			}
		}
	}while (((tolower(thesi) == 'u' || tolower(thesi) == 'd') && (stoixeio <= 0 || stoixeio > cols)) || ((tolower(thesi) == 'l' || tolower(thesi) == 'r') && (stoixeio <= 0 || stoixeio > row)));
	stoixeio--;
	sum=0;
	switch(tolower(thesi)){
        case 'u':
		    for (i=0;i<row;i++){
			    if (table[i][stoixeio] == '#')
				    break;
                else if (table[i][stoixeio] != '.')
                    sum++;
				table[i][stoixeio] = '.';
			}
            break;
        case 'd':
		    for (i=row-1;i>=0;i--){
			    if (table[i][stoixeio] == '#')
				    break;
                else if (table[i][stoixeio] != '.')
                    sum++;
				table[i][stoixeio] = '.';	
			}
            break;
	    case 'l':
		    for (i=0;i<cols;i++){
			    if (table[stoixeio][i] == '#')
				    break;
                else if (table[stoixeio][i] != '.')
                    sum++;
			    table[stoixeio][i] = '.';
			}
            break;
	    case 'r':
		    for (i=cols-1;i>=0;i--){
			    if (table[stoixeio][i] == '#')
				    break;
                else if (table[stoixeio][i] != '.')
                    sum++;
				table[stoixeio][i] = '.';
			}
            break;
    }
	zombies_kill += sum;
	score = (sum * points_of_zombie) + (int)pow(sum, 2);
	total_score += score;
	printf(GREEN"[POINTS]: Your points are %d\n",score);
	printf(BRIGHT_RED"[DAMAGE]: You hit %d zombies\n"RESET,sum);
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './plasmagun.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay plasmagun.wav");
    	#else
        	system("paplay plasmagun.wav");
    	#endif
	}
    move_zombies(table,sound_dir,row,cols);
    print_table(table,row,cols);
}

void bombing(char **table,int row,int cols,int zombies,int sound_dir){
    int a1,a2,sum,score;
	printf(GREEN"[ACTION]: You picked bombing\n");
	printf(GRAY"Give me the coordinates where you want to drop the bomb.\n"RESET);
    do {
        scanf("%d", &a1);
        while (getchar() != '\n')
			; // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
        if (a1 <= 0 || a1 > row){
			printf(RED"Out of bounds\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
    } while (a1 <= 0 || a1 > row);
    do {
        scanf("%d", &a2);
        while (getchar() != '\n')
			; // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
        if (a2 <= 0 || a2 > cols){
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			printf(RED"Out of bounds\n"RESET);
		}
	} while (a2 <= 0 || a2 > cols);
    a2--;
    a1--;
	sum=0;
    if ((a1>=0) && (a1<row) && (a2>=0) && (a2<cols) && (table[a1][a2] >= 1 && table[a1][a2] <= zombies)){ // kentro
        if (table[a1][a2] != '.')
            sum++;
        table[a1][a2] = '.';
	}
    if ((a1>=0) && (a1<row) && (a2-1>=0) && (a2-1<cols) && (table[a1][a2-1] >= 1 && table[a1][a2-1] <= zombies)){ //aristera
        if (table[a1][a2-1] != '.')
		    sum++;
        table[a1][a2-1] = '.';
    }
    if ((a1>=0) && (a1<row) && (a2+1>=0) && (a2+1<cols) && (table[a1][a2+1] >= 1 && table[a1][a2+1] <= zombies)){ //dejia
		if (table[a1][a2+1] != '.')
            sum++;
        table[a1][a2+1] = '.';

	}
    if ((a1-1>=0) && (a1-1<row) && (a2>=0) && (a2<cols) && (table[a1-1][a2] >= 1 && table[a1-1][a2] <= zombies)){ //panw
        if (table[a1-1][a2] != '.')
		    sum++;
        table[a1-1][a2] = '.';
	}
    if ((a1+1>=0) && (a1+1<row) && (a2>=0) && (a2<cols) && (table[a1+1][a2] >= 1 && table[a1+1][a2] <= zombies)){ //katw
        if (table[a1+1][a2] != '.')
		    sum++;
        table[a1+1][a2] = '.';
	}
    if ((a1-1>=0) && (a1-1<row) && (a2-1>=0) && (a2-1<cols) && (table[a1-1][a2-1] >= 1 && table[a1-1][a2-1] <= zombies)){ //panw aristera
	    if (table[a1-1][a2-1] != '.')
	        sum++;
        table[a1-1][a2-1] = '.';
	}
    if ((a1-1>=0) && (a1-1<row) && (a2+1>=0) && (a2+1<cols) && (table[a1-1][a2+1] >= 1 && table[a1-1][a2+1] <= zombies)){ //panw dejia
        if (table[a1-1][a2+1] != '.')
		    sum++;
        table[a1-1][a2+1] = '.';
	}
    if ((a1+1>=0) && (a1+1<row) && (a2-1>=0) && (a2-1<cols) && (table[a1 + 1][a2 - 1] >= 1 && table[a1 + 1][a2-1] <= zombies)){ //katw aristera
        if (table[a1+1][a2-1] != '.')
		    sum++;
        table[a1+1][a2-1] = '.';
	}
    if ((a1+1>=0) && (a1+1<row) && (a2+1>=0) && (a2+1<cols) && (table[a1+1][a2+1] >= 1 && table[a1+1][a2+1] <= zombies)){ // katw dejia
        if (table[a1+1][a2+1] != '.')
		    sum++;
        table[a1+1][a2+1] = '.';
	}
	zombies_kill += sum;
	score = (sum * points_of_zombie) + (int)pow(sum, 2);
	total_score += score;
	printf(GREEN"[POINTS]: Your points are %d\n",score);
	printf(BRIGHT_RED"[DAMAGE]: You hit %d zombies\n"RESET,sum);
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './bomb.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay bomb.wav");
    	#else
        	system("paplay bomb.wav");
    	#endif
	}
	move_zombies(table,sound_dir,row,cols);
    print_table(table, row, cols);
}

void give_neurogun(char **table,int row,int cols,int sound_dir,int **map){
	int r,c,i,j,sum,score,has_neighbor=0;
	char type;
	printf(GREEN"[ACTION]: You picked up the neurogun\n"RESET);
	do {
    	scanf("%d", &r);
    	while (getchar() != '\n')
			; // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
    	if (r <= 0 || r > row){
			printf(RED"Out of bounds\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	} while (r <= 0 || r > row);
    do {
        scanf("%d", &c);
        while (getchar() != '\n')
			; // gia na katharisei h mnhmh kai na fygei to \n pou krataei h scanf
        if (c <= 0 || c > cols){
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			printf(RED"Out of bounds\n"RESET);
		}
	} while (c <= 0 || c > cols);
	r--; 
	c--;
	type = table[r][c];
	if (type == '.' || type == '#'){
		printf(RED"Wrong value: no zombie at that position\n"RESET);
		printf("\a");
		return;
	}
    if (r-1 >= 0 && table[r-1][c] == type) //up
        has_neighbor = 1;
    else if (r+1 < row && table[r+1][c] == type) //down
        has_neighbor = 1;
    else if (c-1 >= 0 && table[r][c-1] == type) //left
        has_neighbor = 1;
    else if (c+1 < cols && table[r][c+1] == type) //right
        has_neighbor = 1;
	if (has_neighbor == 0){
		printf(RED"The neurogun cannot be used on a single zombie\n"RESET);
		printf("\a");
		return;
	}
	for (i=0;i<row;i++)
		for (j=0;j<cols;j++)
			map[i][j]=0;
	sum = neurogun(table,row,cols,r,c,type,map);
	zombies_kill += sum;
	score = (sum * points_of_zombie) + (int)pow(sum,2);
	total_score += score;
	printf(GREEN"[POINTS]: Your points are %d\n",score);
	printf(BRIGHT_RED"[DAMAGE]: You hit %d zombies\n"RESET,sum);
	if (tolower(extra) == 'y'){
		#ifdef _WIN32
        	system("powershell -c \"(New-Object Media.SoundPlayer './neurogun.wav').PlaySync()\"");
    	#elif __APPLE__
        	system("afplay neurogun.wav");
    	#else
        	system("paplay neurogun.wav");
    	#endif
	}
	move_zombies(table,sound_dir,row,cols);
    print_table(table, row, cols);
}

int neurogun(char **table,int row,int cols,int r,int c,char type,int **map){

	if (r<0 || r>=row || c<0 || c>=cols)
		return 0;
	if (table[r][c] != type)
		return 0;
	if (map[r][c] == 1)
		return 0;
	table[r][c] = '.';
	map[r][c] = 1;
	return 1 + neurogun(table,row,cols,r+1,c,type,map) + neurogun(table,row,cols,r,c+1,type,map) + neurogun(table,row,cols,r-1,c,type,map) + neurogun(table,row,cols,r,c-1,type,map);
}

void free_table (char **table, int row)
{
	int i;
	for(i=0;i<row;i++)
		free(table[i]);
	free(table);
	return;
}

int check(char **table,int row, int cols)
{
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<cols;j++)
			if(table[i][j] != '.' && table[i][j] != '#')
				return 0;
	return 1;
}

void move_zombies(char **table, int sound_dir,int row,int cols)
{
	int i,j,k;
    switch(sound_dir){ // up
        case 0:
            for (j=0;j<cols;j++) 
                for (i=0;i<row-1;i++)
                    if (table[i][j] == '.') 
                        for (k=i+1;k<row;k++) {
                            if (table[k][j] == '#')
                                break; //an vroume ktirio stamatame
                            if (table[k][j] != '.') {
                                table[i][j] = table[k][j]; // an vroume zompi to metakinoume ekei pou yparxei keno
                                table[k][j] = '.';
                                break;
                            }
                        }
            break;
	    case 2: // down
            for (j=0;j<cols;j++)
                for (i=row-1;i>0;i--)
                    if (table[i][j] == '.')
                        for (k=i-1;k>=0;k--){
                            if (table[k][j] == '#') 
                                break; // an vroume ktirio stamatame
                            if (table[k][j] != '.') {
                                table[i][j] = table[k][j]; // an vroume zompi to metakinoume sto keno
                                table[k][j] = '.';
                                break;
                            }
                        }
            break;
        case 1: // right
            for (i=0;i<row;i++)
                for (j=cols-1;j>0;j--)
                    if (table[i][j] == '.')
                        for (k=j-1;k>=0;k--) {
                            if (table[i][k] == '#') 
                                break; // an vroume ktirio stamatame
                            if (table[i][k] != '.') {
                                table[i][j] = table[i][k]; // an vroume zompi to metakinoume sto keno
                                table[i][k] = '.';
                                break;
                            }
                        }
            break;
        case 3: // left
            for (i=0;i<row;i++)
                for (j=0;j<cols-1;j++)
                    if (table[i][j] == '.')
                        for (k=j+1;k<cols;k++) {
                            if (table[i][k] == '#') 
                                break; // an vroume ktirio stamatame
                            if (table[i][k] != '.') {
                                table[i][j] = table[i][k]; // an vroume zompi stamatame sto keno
                                table[i][k] = '.';
                                break;
                            }
                        }
            break;
    }
}

int sound_direction(){
    int sound_dir;
	printf(RESET);
	sound_dir = rand()%4;
    printf(GRAY);
	switch(sound_dir){
        case 0:
            printf ("The sound is coming from above\n");
            break;
        case 1:
            printf ("The sound is coming from the right\n");
            break;
        case 2:
            printf ("The sound is coming from below\n");
            break;
        case 3:
            printf ("The sound is coming from the left\n");
            break;
    }
	printf(RESET);
    return sound_dir;
}

char question_FAQ(){
	char answer;
	printf(GRAY"Do you want instructions on how to play the game? [Y/N]\n"RESET);
	do{
		scanf(" %c",&answer);
		if (tolower(answer) != 'y' && tolower(answer) != 'n'){
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
			printf (RED"Wrong value\n"RESET);
		}
	}while(tolower(answer) != 'y' && tolower(answer) != 'n');
	return (char)tolower(answer);
}

void FAQ(){
	int question;
	system_clear();
	welcome();
	printf(BLUE"\n==============================================\n");
	printf("============== "GREEN"GAME FAQ & HELP"BLUE" ===============\n");
	printf("==============================================\n\n"RESET);
	printf(SKY_BLUE"1.  What is the purpose of the game?\n");
	printf("2.  How many courses are there?\n");
	printf("3.  How to use plasmagun\n");
	printf("4.  How to use bombing\n");
	printf("5.  How to use neurogun\n");
	printf("6.  How is the scorer calculated?\n");
	printf("7.  What to do zombies do?\n");
	printf("8.  How to quit from the game\n"RESET);
	printf(YELLOW"Give your choice [1-8]\n"RESET);
	do{
		scanf("%d",&question);
		if (question < 1 || question > 8){
			printf(RED"Wrong Values\n"RESET);
			printf("\a"); // xtypaei ena kampanaki diladi kanei enan hxo
		}
	}while(question < 1 || question > 8);
	printf("\n");
	switch(question){
		case 1:
			printf(ORCHID"The game's purpose is to eliminate all the zombies on the board to get to the next level until the zombie outbreak ends and earth returns back to normal so that people can go back to destroying each other with a third world war\n\n"RESET);
			break;
		case 2: 
			printf(ORCHID"The levels of the game depend on the player\n");
			printf("For example if you start by 2x2 table you will have to beat 7 levels\n");
			printf("If you start with a 7x8 table you will have to beat 2 levels\n");
			printf("The game will be complited when you make it by 9x9 table\n\n"RESET);
			break;
		case 3:
			printf(ORCHID"You use the plasmagun likewise\n");
			printf("When you are asked which weapon you want to use type 'p' or 'P'\n");
			printf("After that, you will be asked to answer the question of where the plasma gun will start from and you will choose one of the four available options.\n");
			printf("'L' or 'l' for (left)\n'R' or 'r' for (right)\n'U or 'u' for (Up)\n'D' or 'd' for (Down)\n\n"RESET);
			break;
		case 4:
			printf(ORCHID"You use bombing likewise\n");
			printf("When you are asked which weapon you want to use type 'b' or 'B'\n");
			printf("After that, you will be asked to answer the question, give the coordinates for the bombing\n");
			printf("You will need to enter coordinated that belong inside the board otherwise an error would pop up and you will be asked again for the coordinates\n\n"RESET);
			break;
		case 5:
			printf(ORCHID"You use the neurogun likewise\n");
			printf("When you are asked which weapon you want to use type 'n' or 'N'\n");
			printf("After that, you will be asked to answer the question, give the coordinates for the neurogun\n");
			printf("You will need to enter coordinated that belong inside the board otherwise an error would pop up and you will be asked again for the coordinates\n\n"RESET);
			break;
		case 6:
			printf(ORCHID"The score is calculated by the following type:\n");
			printf("(zombies * points_of_zombie) + zombies^2\n\n"RESET);
			break;
		case 7:
			printf(ORCHID"The zombies move depending on where the sound is coming from for example if the sound comes from above then the zombies move up\n\n"RESET);
			break;
		case 8:
			printf(ORCHID"To exit the game you need to do the following :\n");
			printf("When you get asked which weapon you want to use you will press 'x' or 'X' and you will automatically exit the game\n\n"RESET);
			break;
	}
}
