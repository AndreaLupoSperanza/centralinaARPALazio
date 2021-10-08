
/*Gestione delle comunicazioni*/
#define CURL_STATICLIB
#include <curl\curl.h> // change the parenthesis by using angled brackets
#include <stdio.h>

/*Gestione delle collezioni*/
#include <vector>
/*Gestione dei file*/
#include <iostream>
#include <fstream>
#include <sstream>
/*Gestione del tempo*/
#include <chrono>
/*Fusorario Globale per Roma*/
auto fusorario = 7200000000000; //In nanosecondi


class ParametriMisura {

public:
    /*Costruttori*/
    ParametriMisura();
    ParametriMisura(int frequenza, int banda, int rbw, int vbw, int span,
        int ib, int attenuazione, int n_medie, int durata_cp,
        int durata_monitoraggio, std::string gestore, std::string tecnologia);
    /*Metodi utili*/
    bool equals(ParametriMisura p);
    void mostraParametri();
    /*Getter*/
    int getFrequenza();
    int getBanda();
    int getRbw();
    int getVbw();
    int getSpan();
    int getIb();
    int getAttenuazione();
    int getN_medie();
    int getDurata_cp();
    int getDurata_monitoraggio();
    std::string getGestore();
    std::string getTecnologia();
private:
    /*Parametri MINIMI necessari per: istruire la centralina e farle effettuare una misura*/
    int frequenza;
    int banda;
    int rbw;
    int vbw;
    int span;
    int ib;
    int attenuazione;
    int n_medie;
    int durata_cp;
    int durata_monitoraggio;
    std::string gestore;
    std::string tecnologia;
};

/*Instanzia un ParametroMisura, DEVE ESSERE COMPLETAMENTE DEFINITO */
ParametriMisura::ParametriMisura() {
    this->frequenza = 0;
    this->banda = 0;
    this->rbw = 0;
    this->vbw = 0;
    this->span = 0;
    this->ib = 0;
    this->attenuazione = 0;
    this->n_medie = 0;
    this->durata_cp = 0;
    this->durata_monitoraggio = 0;
    std::string gestore = "Nessuno";
    std::string tecnologia = "Non specificata";
}
ParametriMisura::ParametriMisura(int frequenza, int banda, int rbw, int vbw, int span,
    int ib, int attenuazione, int n_medie, int durata_cp,
    int durata_monitoraggio, std::string gestore, std::string tecnologia) {
    this->frequenza = frequenza;
    this->banda = banda;
    this->rbw = rbw;
    this->vbw = vbw;
    this->span = span;
    this->ib = ib;
    this->attenuazione = attenuazione;
    this->n_medie = n_medie;
    this->durata_cp = durata_cp;
    this->durata_monitoraggio = durata_monitoraggio;
    this->gestore = gestore;
    this->tecnologia = tecnologia;
}


/*
* Descrive secondo quali criteri due istanze di ParametriMisura sono da considerarsi uguali.
*/
bool ParametriMisura::equals(ParametriMisura p) {
    return (this->frequenza == p.getFrequenza()) && (this->banda == p.getBanda()) &&
        (this->rbw == p.getRbw()) && (this->vbw == p.getVbw()) &&
        (this->span == p.getSpan()) && (this->ib == p.getIb()) &&
        (this->attenuazione == p.getAttenuazione()) && (this->n_medie == p.getN_medie()) &&
        (this->durata_cp == p.getDurata_cp()) && (this->durata_monitoraggio == p.getDurata_monitoraggio()) &&
        (this->gestore.compare(p.getGestore()) == 0) && (this->tecnologia.compare(p.getTecnologia()) == 0);
}

/*
* Mostra sul terminale i Parametri che descrivono come deve essere fatta la Misura.
*/
void ParametriMisura::mostraParametri() {
    std::cout << "Info: " << this->frequenza << " " << this->banda << " " << this->rbw << " "
        << this->vbw << " " << this->span << " " << this->ib << " "
        << this->attenuazione << " " << this->n_medie << " " << this->durata_cp << " "
        << this->durata_monitoraggio << " " << this->gestore << " " << this->tecnologia << " " << std::endl;
}

/*Setter e Getter vari*/

int ParametriMisura::getFrequenza() {
    return this->frequenza;
}
int ParametriMisura::getBanda() {
    return this->banda;
}
int ParametriMisura::getRbw() {
    return this->rbw;
}
int ParametriMisura::getVbw() {
    return this->vbw;
}
int ParametriMisura::getSpan() {
    return this->span;
}
int ParametriMisura::getIb() {
    return this->ib;
}
int ParametriMisura::getAttenuazione() {
    return this->attenuazione;
}
int ParametriMisura::getN_medie() {
    return this->n_medie;
}
int ParametriMisura::getDurata_cp() {
    return this->durata_cp;
}
int ParametriMisura::getDurata_monitoraggio() {
    return this->durata_monitoraggio;
}
std::string ParametriMisura::getGestore() {
    return this->gestore;
}
std::string ParametriMisura::getTecnologia() {
    return this->tecnologia;
}

/*
* Classe che descrive una Collezione di ParametriMisura,
* Permette di memorizzare parametri multipli per effettuare misure multiple.
* Permette di salvare i parametri multipli su di un File, .txt, chiamato ParametriMisura.txt
* Permette di caricare i parametri multipli da un File, .txt, chiamato ParametriMisura.txt
*/
class CollezioneParametriMisura {
public:
    CollezioneParametriMisura();
    void inserisciParMis(ParametriMisura p);
    bool eliminaParMis(ParametriMisura p);
    void mostraParMis();
    void salvaSuFile();
    void caricaDaFile();
    std::vector<ParametriMisura> getCollezioneParametri();

private:
    std::vector<ParametriMisura> memorizzate;
};

/*Costruttore di Collezione*/
CollezioneParametriMisura::CollezioneParametriMisura() {
    /*Utilizzabile per inserire all'avvio del software direttamente delle bande da misurare*/
}

/*
* Aggiunge un elemento in coda al vettore che rappresenta i ParametriMisura.
*/
void CollezioneParametriMisura::inserisciParMis(ParametriMisura p) {
    this->memorizzate.push_back(p);
}

/*
* Elimina dalla collezione un Parametro di Misura indicato,
* i parametri di eliminazione sono descritti dalla funzione equals presente in ParametriMisura.
*/
bool CollezioneParametriMisura::eliminaParMis(ParametriMisura p) {
    for (auto it = memorizzate.begin(); it != memorizzate.end(); ++it)
        if ((*it).equals(p)) {
            memorizzate.erase(it);
            return  1;
        }
    return 0;
}

/*
* Mostra a terminale tutti i ParametriMisura memorizzati all'interno della collezione.
*/
void CollezioneParametriMisura::mostraParMis() {
    for (auto it = this->memorizzate.begin(); it != this->memorizzate.end(); ++it) {
        (*it).mostraParametri();
    }
}

/*
* Permette di ottenere il vettore che rappresenta la Collezione di ParametriMisura.
* Le misure andranno effettuate imponendo un ciclo su questo vettore,
* dove da ogni elemento si estraggono i parametri necessari alla misura.
*/
std::vector<ParametriMisura> CollezioneParametriMisura::getCollezioneParametri() {
    return this->memorizzate;
}

/*
* Permette di salvare su un file la Collezione di ParametriMisura presente al momento della chiamata.
*
*/
void CollezioneParametriMisura::salvaSuFile() {
    std::ofstream myfile("parametrimisura.txt", std::ofstream::out);

    for (auto it = this->memorizzate.begin(); it != this->memorizzate.end(); ++it) {

        myfile << (*it).getFrequenza() << " " << (*it).getBanda() << " " << (*it).getRbw() << " " <<
            (*it).getVbw() << " " << (*it).getSpan() << " " << (*it).getIb() << " " <<
            (*it).getAttenuazione() << " " << (*it).getN_medie() << " " << (*it).getDurata_cp() << " " <<
            (*it).getDurata_monitoraggio() << " " << (*it).getGestore() << " " << (*it).getTecnologia() << " " << "\n";

    }

    myfile.close();
}

/*
* Permette di caricare da File una Collezione di ParametriMisura, sovrascrivendo quella attuale.
*/
void CollezioneParametriMisura::caricaDaFile() {
    //Dati da estrarre riga per riga
    int frequenza;
    int banda;
    int rbw;
    int vbw;
    int span;
    int ib;
    int attenuazione;
    int n_medie;
    int durata_cp;
    int durata_monitoraggio;
    std::string gestore;
    std::string tecnologia;

    //Variabili di appoggio del file
    std::ifstream myFile("parametrimisura.txt");
    std::string linea;

    while (getline(myFile, linea)) {
        // Dump the contents of the file to cout.
        std::istringstream iss(linea);

        if (!(iss >> frequenza >> banda >> rbw >> vbw >> span >> ib >> attenuazione >> n_medie >> durata_cp >> durata_monitoraggio >> gestore >> tecnologia)) { break; }
        else {
            this->inserisciParMis(ParametriMisura(frequenza, banda, rbw, vbw, span, ib, attenuazione, n_medie, durata_cp, durata_monitoraggio, gestore, tecnologia));
        }


    }
    myFile.close();
    this->mostraParMis();
}


class Misura {

public:
    Misura();
    Misura(ParametriMisura p, float channelPower);
    Misura(ParametriMisura p, float channelPower, std::string dataOra);
    bool equals(Misura m);
    ParametriMisura getParametriMisura();
    float getChannelPower();
    std::string getDataOra();
    void setChannelPower(float channelPower);
    bool setDataOra();// InfluxDB richiede: 1677-09-21T00:12:43.145224194Z ossia aaaa-mm-ggToo:mm:ssZ

private:
    ParametriMisura p;
    float channelPower;
    std::string dataOra;
};

/*
* Costruttore di base (NON UTILIZZARLO MAI)
*/
Misura::Misura() {
    this->p = ParametriMisura();
    this->channelPower = 0;
    this->dataOra = "Assente";
}
/*
* Costruttore Misura con setUp Automatico dell'orario di misurazione
*/
Misura::Misura(ParametriMisura p, float channelPower) {
    this->p = p;
    this->channelPower = channelPower;
    this->dataOra = std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + fusorario);
}
/*
* Costruttore con Misura con setUp Manuale dell'orario di misurazione.
*/
Misura::Misura(ParametriMisura p, float channelPower, std::string dataOra) {
    this->p = p;
    this->channelPower = channelPower;
    this->dataOra = dataOra;
}

/*
* Metodo necessario per verificare l'uguaglianza o meno tra due misure.
*/
bool Misura::equals(Misura m) {
    return
        (this->channelPower == m.getChannelPower()) &&
        ((this->dataOra.compare(m.getDataOra())) == 0) &&
        ((this->p.getFrequenza()) == (m.getParametriMisura().getFrequenza())) &&
        (this->p.getFrequenza() == m.getParametriMisura().getFrequenza()) &&
        (this->p.getBanda() == m.getParametriMisura().getBanda()) &&
        (this->p.getRbw() == m.getParametriMisura().getRbw()) &&
        (this->p.getVbw() == m.getParametriMisura().getVbw()) &&
        (this->p.getSpan() == m.getParametriMisura().getSpan()) &&
        (this->p.getIb() == m.getParametriMisura().getIb()) &&
        (this->p.getAttenuazione() == m.getParametriMisura().getAttenuazione()) &&
        (this->p.getN_medie() == m.getParametriMisura().getN_medie()) &&
        (this->p.getDurata_cp() == m.getParametriMisura().getDurata_cp()) &&
        (this->p.getDurata_monitoraggio() == m.getParametriMisura().getDurata_monitoraggio()) &&
        ((this->p.getGestore().compare(m.getParametriMisura().getGestore())) == 0) &&
        ((this->p.getTecnologia().compare(m.getParametriMisura().getTecnologia())) == 0);
}

/*Getter e Setter*/
float Misura::getChannelPower() {
    return this->channelPower;
}
ParametriMisura Misura::getParametriMisura() {
    return this->p;
}
std::string Misura::getDataOra() {
    return this->dataOra;
}
void Misura::setChannelPower(float channelPower) {
    this->channelPower = channelPower;
}

/*
* Struttura dati principale che permette di contenere, mantenere, salvare su file e/o Cloud, caricare da file le misure.
*/
class CollezioneMisure {
public:
    CollezioneMisure();
    void inserisciMis(Misura p);
    bool eliminaMis(Misura p);
    void mostraMis();
    void salvaTutteMisureSuFile();
    void salvaMisuraSuFile(Misura daSalvare);
    void caricaDaFile();
    void salvaInCloud();
    std::vector<Misura> getCollezioneMisure();

private:
    std::vector<Misura> memorizzate;
};

/*Costruttore vuoto di misura*/
CollezioneMisure::CollezioneMisure() {
}

std::vector<Misura> CollezioneMisure::getCollezioneMisure() {
    return this->memorizzate;
}

/*
* Inserisce in memoria la misura paassata come parametro
*/
void CollezioneMisure::inserisciMis(Misura p) {
    this->memorizzate.push_back(p);
}

/*
* Elimina la misura perfettamente identica a quella passata come parametro.
*/
bool CollezioneMisure::eliminaMis(Misura p) {
    for (auto it = memorizzate.begin(); it != memorizzate.end(); ++it)
        if ((*it).equals(p)) {
            memorizzate.erase(it);
            return  1;
        }
    return 0;
}

/*
* Mostra su terminale tutte le misure presenti attualmente in memoria.
*/
void CollezioneMisure::mostraMis() {
    for (auto it = this->memorizzate.begin(); it != this->memorizzate.end(); ++it) {
        (*it).getParametriMisura().mostraParametri();
        std::cout << (*it).getChannelPower() << (*it).getDataOra() << std::endl;
    }
}

/*
* Salva le misure attualmente presenti in memoria su file.
*/
void CollezioneMisure::salvaTutteMisureSuFile() {
    std::ofstream myfile("misure.txt", std::ios_base::app | std::ios_base::in);

    for (auto it = this->memorizzate.begin(); it != this->memorizzate.end(); ++it) {

        myfile << (*it).getParametriMisura().getFrequenza() << " " <<
            (*it).getParametriMisura().getBanda() << " " <<
            (*it).getParametriMisura().getRbw() << " " <<
            (*it).getParametriMisura().getVbw() << " " <<
            (*it).getParametriMisura().getSpan() << " " <<
            (*it).getParametriMisura().getIb() << " " <<
            (*it).getParametriMisura().getAttenuazione() << " " <<
            (*it).getParametriMisura().getN_medie() << " " <<
            (*it).getParametriMisura().getDurata_cp() << " " <<
            (*it).getParametriMisura().getDurata_monitoraggio() << " " <<
            (*it).getParametriMisura().getGestore() << " " <<
            (*it).getParametriMisura().getTecnologia() << " " <<
            (*it).getChannelPower() << " " <<
            (*it).getDataOra() << " " << "\n";

    }

    myfile.close();
}

/*
* Permette il salvataggio sul file: misure.txt, in append, di una singola misura passata come parametro
*/
void CollezioneMisure::salvaMisuraSuFile(Misura daSalvare) {
    std::fstream myfile("misure.txt", std::ios_base::app | std::ios_base::in);

    myfile << daSalvare.getParametriMisura().getFrequenza() << " " <<
        daSalvare.getParametriMisura().getBanda() << " " <<
        daSalvare.getParametriMisura().getRbw() << " " <<
        daSalvare.getParametriMisura().getVbw() << " " <<
        daSalvare.getParametriMisura().getSpan() << " " <<
        daSalvare.getParametriMisura().getIb() << " " <<
        daSalvare.getParametriMisura().getAttenuazione() << " " <<
        daSalvare.getParametriMisura().getN_medie() << " " <<
        daSalvare.getParametriMisura().getDurata_cp() << " " <<
        daSalvare.getParametriMisura().getDurata_monitoraggio() << " " <<
        daSalvare.getParametriMisura().getGestore() << " " <<
        daSalvare.getParametriMisura().getTecnologia() << " " <<
        daSalvare.getChannelPower() << " " <<
        daSalvare.getDataOra() << "\n";

    myfile.close();
}

/*
* Permette di caricare da File una Collezione di ParametriMisura, sovrascrivendo quella attuale.
*/
void CollezioneMisure::caricaDaFile() {

    //Dati da estrarre riga per riga
    int frequenza;
    int banda;
    int rbw;
    int vbw;
    int span;
    int ib;
    int attenuazione;
    int n_medie;
    int durata_cp;
    int durata_monitoraggio;
    std::string gestore;
    std::string tecnologia;
    float channelPower;
    std::string dataOra;

    //Variabili di appoggio del file
    std::ifstream myFile("misure.txt");
    std::string linea;

    while (getline(myFile, linea)) {
        // Dump the contents of the file to cout.
        std::istringstream iss(linea);


        if (!(iss >> frequenza >> banda >> rbw >> vbw >> span >> ib >> attenuazione >> n_medie >> durata_cp >> durata_monitoraggio >> gestore >> tecnologia >> channelPower >> dataOra)) { break; }
        else {
            this->inserisciMis(Misura(ParametriMisura(frequenza, banda, rbw, vbw, span, ib, attenuazione, n_medie, durata_cp, durata_monitoraggio, gestore, tecnologia), channelPower, dataOra));
        }


    }
    myFile.close();

    this->mostraMis();

}
/*
* Metodo permette il salvataggio in cloud tramite HTTP.
*/
void CollezioneMisure::salvaInCloud() {
    CURL* curl;
    CURLcode res;

    /* Dati del server InfluxDB*/
    std::string Ipv4Server = "192.168.1.77";
    std::string portaServer = "8086";
    std::string nomeDb = "myDB";
    std::string utentePassword = "admin:admin";
    std::string nomeTabella = "misure";

    std::string URL, upData;
    URL = "http://" + Ipv4Server + ":" + portaServer + "/write?db=" + nomeDb;
    std::cout << "URL: " << URL << std::endl;

    for (auto it = this->memorizzate.begin(); it != this->memorizzate.end(); ++it) {
        //freq, banda, rbw, vbw, span, ib, attenuazione, n_medie, durata_cp, durata_monitoraggio, gestore, tecnologia, channel_power
        upData = nomeTabella + ",freq=" + std::to_string((*it).getParametriMisura().getFrequenza()).c_str()  + 
                                " banda="+ std::to_string((*it).getParametriMisura().getBanda()).c_str() +
                                ",rbw=" + std::to_string((*it).getParametriMisura().getRbw()).c_str() +
                                ",vbw=" + std::to_string((*it).getParametriMisura().getVbw()).c_str() +
                                ",span=" + std::to_string((*it).getParametriMisura().getSpan()).c_str() +
                                ",ib=" + std::to_string((*it).getParametriMisura().getIb()).c_str() +
                                ",attenuazione=" + std::to_string((*it).getParametriMisura().getAttenuazione()).c_str() +
                                ",n_medie=" + std::to_string((*it).getParametriMisura().getN_medie()).c_str() +
                                ",durata_cp=" + std::to_string((*it).getParametriMisura().getDurata_cp()).c_str() +
                                ",durata_monitoraggio=" + std::to_string((*it).getParametriMisura().getDurata_monitoraggio()).c_str() +
                                ",gestore=\"" + (*it).getParametriMisura().getGestore().c_str() + "\"" +
                                ",tecnologia=\"" + (*it).getParametriMisura().getTecnologia().c_str() + "\""
                                ",channel_power=" + std::to_string((*it).getChannelPower()).c_str() + 
                                " " + (*it).getDataOra().c_str();


        std::cout << "Dati: " << upData << std::endl;
        /* Inizio Curl Globale in Windows */
        curl_global_init(CURL_GLOBAL_ALL);

        /* Inizio di una Culr */
        curl = curl_easy_init();
        if (curl) {
            /* URL destinatario della Curl */
            curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
            /*Settare Username e Password*/
            curl_easy_setopt(curl, CURLOPT_USERPWD, utentePassword.c_str());
            /* Dati da postare */
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upData.c_str());
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                fprintf(stderr, "Curl Fallista, motivo: %s\n",
                    curl_easy_strerror(res));

            /* Fine Curl locale */
            curl_easy_cleanup(curl);
        }
        /* Fine Crul Globale */
        curl_global_cleanup();

    }
}



int main(void)
{

    /*Il FILE misure.txt organizza la misurazione nel seguente modo: */
    /*  Frequenzza Banda Rbw Vbw Span Ib Attenuazione N_medie Durata_cp Durata_monitoraggio Gestore Tecnologia ChannelPower TimeStampInNanosecondi\n */

    CollezioneMisure cm;

    std::cout << "Inizio caricamento misure da file" << std::endl;
    cm.caricaDaFile();
    std::cout << "Fine caricamento da file da File" << std::endl;
    std::cout << "\n\n" << std::endl;
    std::cout << "Inizio upload su Cloud" << std::endl;
    cm.salvaInCloud();
    std::cout << "Fine upload su Cloud" << std::endl;
    
}
