package game.datamodel.Model;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
@Data
public class Word {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    private String word;

    private Integer difficulty;

    public void setWord(String s) {
        word = s;
    }

    public void setDifficulty() {
        difficulty = word.length();
    }

    public String getWord() {
        return word;
    }

    public Integer getDifficulty() {
        return difficulty;
    }

    public Word(String s) {
        word = s;
        difficulty = s.length();
    }

    public Word(){}
}
