package game.datamodel.DAO;

import game.datamodel.Model.Player;
import lombok.Data;

@Data
public class PlayerDAO {
    private Integer id;

    private Integer exp;

    private Integer level;

    private Integer totalPassedStage;

    public PlayerDAO(Player p){
        id = p.getId();
        exp = p.getExp();
        level = p.getLevel();
        totalPassedStage = p.getTotalPassedStage();
    }
}
