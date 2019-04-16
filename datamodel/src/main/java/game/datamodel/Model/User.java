package game.datamodel.Model;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String username;

    private String password;

    private Integer exp;

    private Integer totalPassedStage;

    private Integer numberOfQuestions;

    public User() {
    }

    public User(String username, String password, Integer exp, Integer totalPassedStage, Integer numberOfQuestions) {
        this.username = username;
        this.password = password;
        this.exp = exp;
        this.totalPassedStage = totalPassedStage;
        this.numberOfQuestions = numberOfQuestions;
    }
}
