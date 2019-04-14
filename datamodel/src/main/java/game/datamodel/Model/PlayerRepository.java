package game.datamodel.Model;

import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

public interface PlayerRepository extends CrudRepository<Player, Integer> {
    List<Player> findAll();

    Optional<Player> findById(Integer id);

    @Query(value = "update Player set exp = ?1, level = ?2, totalPassedStage = ?3 where id = ?4")
    @Modifying
    @Transactional
    void update(Integer exp, Integer level, Integer totalPassedStage, Integer id);
}
