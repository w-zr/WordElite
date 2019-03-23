package game.datamodel.Model;

import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface PlayerRepository extends JpaRepository<Player, Integer> {
    List<Player> findAll();

    Optional<Player> findById(Integer id);
}
