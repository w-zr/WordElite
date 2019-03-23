package game.datamodel.DAO;

import game.datamodel.Model.Questioner;
import lombok.Data;

@Data
public class QuestionerDAO {
    private Integer id;

    private Integer level;

    private Integer numberOfQuestions;

    public QuestionerDAO(Questioner q) {
        id = q.getId();
        level = q.getLevel();
        numberOfQuestions = q.getNumberOfQuestions();
    }
}
