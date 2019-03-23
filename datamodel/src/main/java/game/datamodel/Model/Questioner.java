package game.datamodel.Model;

import lombok.Data;

import javax.persistence.*;

@Entity
@Data
public class Questioner {
    @Id
    private Integer id;

    private Integer level;

    private Integer numberOfQuestions;

    @OneToOne(fetch = FetchType.LAZY)
    @MapsId
    private User user;

    public Questioner(Integer level, Integer numberOfQuestions, User user) {
        this.level = level;
        this.numberOfQuestions = numberOfQuestions;
        this.user = user;
    }
}
