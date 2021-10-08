// WindowsCentralina.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
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


int main()
{
    /*Parte di solo esempio da cancellare prima di caricare i software sui miniPC*/
    /*
    CollezioneParametriMisura cpmp;

    ParametriMisura pma = ParametriMisura(100, 100, 12, 12, 10, 12, 0, 50, 1, 1, "Illiad", "4G");
    ParametriMisura pmb = ParametriMisura(200, 100, 12, 12, 10, 12, 0, 50, 1, 1, "Tim", "4G");
    ParametriMisura pmc = ParametriMisura(300, 100, 12, 12, 10, 12, 0, 50, 1, 1, "Vodafone", "4G");

    cpmp.inserisciParMis(pma);
    cpmp.inserisciParMis(pmb);
    cpmp.inserisciParMis(pmc);

    cpmp.salvaSuFile();

    /*Fine parte di solo esempio*/


    /*Il FILE ParametriMisura.txt organizza la misurazione nel seguente modo: */
    /*  Frequenzza Banda Rbw Vbw Span Ib Attenuazione N_medie Durata_cp Durata_monitoraggio Gestore Tecnologia \n */


    /*Parte da includere in cima al codice della centralina, FUORI DAL LOOP INFINITO PER LE MISURE*/
    CollezioneParametriMisura cpm;
    CollezioneMisure cm;

    cpm.caricaDaFile();

    std::vector<ParametriMisura> pm = cpm.getCollezioneParametri();

    /*Parte da inserire nel loop per le misurazioni*/

    /*Ciclo sulle 27 bande di frequenza da analizzare*/
    for (auto it = pm.begin(); it != pm.end(); ++it) {
        /*Per fare la misurazione abbiamo bisogno dei parametri, qui di sotto hai tutti i parametri per la misura*/
        (*it).getFrequenza();
        (*it).getBanda();
        (*it).getRbw();
        (*it).getVbw();
        (*it).getSpan();
        (*it).getIb();
        (*it).getAttenuazione();
        (*it).getN_medie();
        (*it).getDurata_cp();
        (*it).getDurata_monitoraggio();

        /* Qui contatti la centralina passando i parametri di sopra per fare la misura ed ottenere la Channel power */

        float channelPower = 0; //Sostituisci il risultato della Channel Power

        /* Ci prendiamo anche gli ultimi due parametri della misura, il gestore e la tecnologia analizzata */
        Misura misuraDaSalvare = Misura(ParametriMisura((*it).getFrequenza(), (*it).getBanda(), (*it).getRbw(), (*it).getVbw(),
            (*it).getSpan(), (*it).getIb(), (*it).getAttenuazione(), (*it).getN_medie(),
            (*it).getDurata_cp(), (*it).getDurata_monitoraggio(), (*it).getGestore(),
            (*it).getTecnologia()), channelPower);
        
        cm.inserisciMis(misuraDaSalvare); //Salvataggio nella struttura dati interna, ma puoi anche evitare se scrivi diretto sul file
        cm.salvaMisuraSuFile(misuraDaSalvare);//Salvataggio sul file in append

    }

    /*Penso qui inserirai la il tempo di attesa tra un analisi e l'altra prima di ricominciare il loop per nuove misure*/

}
