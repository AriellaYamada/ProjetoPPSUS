import java.util.List;

public class main {

    public static void main(String[] args) {

        FileReader reader = new FileReader("Ariene.csv");


        CSVReader<Person> csvPersonReader = new CSVReaderBuilder<Person>(reader).entryParser(new PersonEntryParser()).build();
        List<Person> persons = csvPersonReader.readAll();

    }
}
