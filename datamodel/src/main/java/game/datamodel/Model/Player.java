package game.datamodel.Model;

import lombok.Data;

import javax.persistence.*;

@Entity
@Data
public class Player {
    @Id
    private Integer id;

    private Integer exp;

    private Integer level;

    private Integer totalPassedStage;

    @OneToOne(fetch = FetchType.LAZY)
    @MapsId
    private User user;

    public Player(Integer exp, Integer level, Integer totalPassedStage, User user) {
        this.exp = exp;
        this.level = level;
        this.totalPassedStage = totalPassedStage;
        this.user = user;
    }
}
